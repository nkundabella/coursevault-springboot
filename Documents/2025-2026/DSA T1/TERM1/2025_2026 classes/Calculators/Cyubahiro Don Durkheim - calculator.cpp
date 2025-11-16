#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <cmath>
#include <cctype>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <vector>
#include <string>

//======================== util ========================//
static inline bool isFinite(double x){ return std::isfinite(x); }
static inline void alert(const std::string& s){ fl_alert("%s", s.c_str()); }
static inline std::string trim(const std::string& s){
    std::string::size_type l = s.find_first_not_of(" \t\r\n");
    if(l==std::string::npos) return "";
    std::string::size_type r = s.find_last_not_of(" \t\r\n");
    return s.substr(l, r-l+1);
}
static inline void replaceChar(std::string &s, char from, char to){
    for(size_t i=0;i<s.size();++i) if(s[i]==from) s[i]=to;
}

//================== expression evaluator ==================//
enum TokT { NUM, PLUS, MINUS, MUL, DIV, LP, RP, END, BAD, PERCENT };
struct Tok{ TokT t; double v; Tok(TokT tt=END,double vv=0):t(tt),v(vv){} };

struct Lexer {
    const char* p;
    explicit Lexer(const std::string& s):p(s.c_str()){}
    Tok next(){
        while(*p && std::isspace((unsigned char)*p)) ++p;
        if(!*p) return Tok(END);
        char c=*p++;
        switch(c){
            case '+': return Tok(PLUS);
            case '-': return Tok(MINUS);
            case '*': case 'x': case 'X': return Tok(MUL);
            case '/': case 0xF7: return Tok(DIV); // ÷
            case '(': return Tok(LP);
            case ')': return Tok(RP);
            case '%': return Tok(PERCENT);
            default:
                if(std::isdigit((unsigned char)c) || c=='.'){
                    char buf[128]; int i=0; buf[i++]=c;
                    while(*p && (std::isdigit((unsigned char)*p) || *p=='.')){
                        if(i<120) buf[i++]=*p; ++p;
                    }
                    buf[i]='\0';
                    errno=0;
                    char* e=NULL;
                    double v=strtod(buf,&e);
                    if(e==buf || errno==ERANGE || !isFinite(v)) return Tok(BAD);
                    return Tok(NUM,v);
                }
                return Tok(BAD);
        }
    }
};

static bool toRPN(const std::string& expr, std::vector<Tok>& out, std::string& err){
    Lexer L(expr);
    std::vector<Tok> op;
    Tok last=Tok(END);
    auto prec=[&](TokT t)->int{
        if(t==PLUS||t==MINUS) return 1;
        if(t==MUL||t==DIV)    return 2;
        return 0;
    };
    auto isOp=[&](TokT t){return t==PLUS||t==MINUS||t==MUL||t==DIV;};

    for(;;){
        Tok tk=L.next();
        if(tk.t==BAD){ err="Error: invalid token"; return false; }
        if(tk.t==END) {
            while(!op.empty()){
                TokT t=op.back().t;
                op.pop_back();
                if(t==LP){ err="Error: mismatched '('"; return false; }
                out.push_back(Tok(t));
            }
            break;
        }
        if(tk.t==NUM){
            out.push_back(tk);
            last=tk;
        } else if(tk.t==PERCENT){
            if(!(last.t==NUM || last.t==RP)){ err="Error: stray %"; return false; }
            out.push_back(tk);
            last=tk;
        } else if(isOp(tk.t)){
            if(last.t==END || last.t==LP || isOp(last.t)){
                if(tk.t==MINUS){ out.push_back(Tok(NUM,0.0)); }
                else { err="Error: operator position"; return false; }
            }
            while(!op.empty() && isOp(op.back().t) && prec(op.back().t)>=prec(tk.t)){
                out.push_back(op.back()); op.pop_back();
            }
            op.push_back(tk);
            last=tk;
        } else if(tk.t==LP){
            op.push_back(tk);
            last=tk;
        } else if(tk.t==RP){
            bool found=false;
            while(!op.empty()){
                TokT t=op.back().t; op.pop_back();
                if(t==LP){ found=true; break; }
                out.push_back(Tok(t));
            }
            if(!found){ err="Error: mismatched ')'"; return false; }
            last=tk;
        }
    }
    return true;
}

static bool evalRPN(const std::vector<Tok>& rpn, double& out, std::string& err){
    std::vector<double> st;
    for(size_t i=0;i<rpn.size();++i){
        Tok tk=rpn[i];
        if(tk.t==NUM){ st.push_back(tk.v); }
        else if(tk.t==PERCENT){
            if(st.empty()){ err="Error: % without value"; return false; }
            double a=st.back(); st.pop_back();
            double v=a/100.0;
            if(!isFinite(v)){ err="Error: overflow"; return false; }
            st.push_back(v);
        } else {
            if(st.size()<2){ err="Error: missing operand"; return false; }
            double b=st.back(); st.pop_back();
            double a=st.back(); st.pop_back();
            double v=0.0;
            switch(tk.t){
                case PLUS: v=a+b; break;
                case MINUS:v=a-b; break;
                case MUL:  v=a*b; break;
                case DIV:
                    if(b==0.0){ err="Error: ÷0"; return false; }
                    v=a/b; break;
                default: err="Error: bad op"; return false;
            }
            if(!isFinite(v)){ err="Error: overflow"; return false; }
            st.push_back(v);
        }
    }
    if(st.size()!=1){ err="Error: malformed expression"; return false; }
    out=st.back();
    return true;
}

static bool evaluate(const std::string& raw, double& val, std::string& err){
    std::string expr=trim(raw);
    if(expr.empty()){ err="Error: empty input"; return false; }
    replaceChar(expr, ',', '.'); // allow comma decimals
    // replace unicode ×, ÷ with ascii
    for(size_t i=0;i<expr.size();++i){
        if((unsigned char)expr[i]==0xC3 && i+1<expr.size()){
            if((unsigned char)expr[i+1]==0x97){ expr[i]='*'; expr.erase(i+1,1); } // ×
            else if((unsigned char)expr[i+1]==0xB7){ expr[i]='/'; expr.erase(i+1,1); } // ÷ (fallback)
        }
    }
    std::vector<Tok> rpn;
    if(!toRPN(expr,rpn,err)) return false;
    return evalRPN(rpn,val,err);
}

static std::string fmt12(double v){
    std::ostringstream oss;
    oss.unsetf(std::ios::floatfield); // default float format
    oss.precision(12);
    oss << v;
    return oss.str();
}

//================== styled button helper ==================//
static Fl_Button* mk_btn(int x,int y,int w,int h,const char* label,
                         Fl_Color bg, Fl_Color sel,
                         Fl_Boxtype boxtype=FL_ROUND_UP_BOX, int labsz=18){
    Fl_Button* b=new Fl_Button(x,y,w,h,label);
    b->box(boxtype);
    b->color(bg);
    b->selection_color(sel);
    b->labelsize(labsz);
    b->labelfont(FL_HELVETICA_BOLD);
    return b;
}

//================== app ==================//
struct App: public Fl_Window{
    Fl_Box* history;
    Fl_Input* entry;
    Fl_Box* result;
    std::vector<Fl_Button*> buttons;
    std::string last_expr; double last_value;

    App(int W,int H):Fl_Window(W,H,"Calculator"),history(0),entry(0),result(0),last_value(0.0){
        color(fl_rgb_color(245,245,247));
        Fl::background(245,245,247);
        Fl::foreground(30,30,33);

        int pad=14;
        int display_h=90;
        history=new Fl_Box(pad,pad,W-2*pad,24,"");
        history->labelfont(FL_HELVETICA_BOLD);
        history->labelsize(16);
        history->align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
        history->box(FL_FLAT_BOX);

        entry=new Fl_Input(pad,pad+26,W-2*pad-140,36);
        entry->textfont(FL_HELVETICA);
        entry->textsize(18);
        entry->box(FL_FLAT_BOX);
        entry->color(fl_rgb_color(255,255,255));
        entry->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
        entry->callback([](Fl_Widget*, void* ud){ ((App*)ud)->press_equals(); }, this);

        result=new Fl_Box(pad+(W-2*pad-140)+10,pad+26,130,36,"");
        result->labelfont(FL_HELVETICA_BOLD);
        result->labelsize(22);
        result->align(FL_ALIGN_RIGHT|FL_ALIGN_INSIDE);
        result->box(FL_FLAT_BOX);

        Fl_Box* sep=new Fl_Box(pad,pad+26+36+8,W-2*pad,2,"");
        sep->box(FL_FLAT_BOX); sep->color(fl_rgb_color(230,230,233));

        // keypad
        int grid_y = pad+display_h;
        int bw=64, bh=44, gap=10;
        int left = pad;
        Fl_Color keyBG = fl_rgb_color(238,240,242);
        Fl_Color keySel= fl_rgb_color(210,214,219);
        Fl_Color keyOpBG = fl_rgb_color(224,228,232);
        Fl_Color keyEqBG = fl_rgb_color(56,168,68);
        Fl_Color keyEqSel= fl_rgb_color(42,128,52);

        auto place=[&](int col,int row,const char* lbl, Fl_Color bg, Fl_Color sel,
                       int colspan=1, int rowspan=1)->Fl_Button*{
            int x = left + col*(bw+gap);
            int y = grid_y + row*(bh+gap);
            int w = colspan*bw + (colspan-1)*gap;
            int h = rowspan*bh + (rowspan-1)*gap;
            Fl_Button* b=mk_btn(x,y,w,h,lbl,bg,sel,FL_ROUND_UP_BOX,18);
            buttons.push_back(b);
            return b;
        };

        // Row 0
        place(0,0,"7",keyBG,keySel);
        place(1,0,"8",keyBG,keySel);
        place(2,0,"9",keyBG,keySel);
        place(3,0,"÷",keyOpBG,keySel);
        place(4,0,"⌫",keyOpBG,keySel);
        place(5,0,"C", keyOpBG,keySel);

        // Row 1
        place(0,1,"4",keyBG,keySel);
        place(1,1,"5",keyBG,keySel);
        place(2,1,"6",keyBG,keySel);
        place(3,1,"×",keyOpBG,keySel);
        place(4,1,"(",keyOpBG,keySel);
        place(5,1,")",keyOpBG,keySel);

        // Row 2
        place(0,2,"1",keyBG,keySel);
        place(1,2,"2",keyBG,keySel);
        place(2,2,"3",keyBG,keySel);
        place(3,2,"-",keyOpBG,keySel);
        place(4,2,"x²",keyOpBG,keySel);
        place(5,2,"√", keyOpBG,keySel);

        // Row 3
        place(0,3,"0",keyBG,keySel);
        place(1,3,",",keyOpBG,keySel);
        place(2,3,"%",keyOpBG,keySel);
        place(3,3,"+",keyOpBG,keySel);
        Fl_Button* eq = place(4,3,"=",keyEqBG,keyEqSel,2,1);
        eq->labelcolor(FL_WHITE);

        for(size_t i=0;i<buttons.size();++i){
            buttons[i]->callback([](Fl_Widget* w, void* ud){
                App* self=(App*)ud;
                const char* lbl=((Fl_Button*)w)->label();
                self->handle_button(std::string(lbl?lbl:""));
            }, this);
        }

        end();
        resizable(this);
        entry->take_focus();
        size_range(480, 420, 900, 700);
    }

    //----------- actions -----------//
    void handle_button(const std::string& s){
        if(s=="C"){ entry->value(""); result->label(""); history->label(""); return; }
        if(s=="⌫"){ do_backspace(); return; }
        if(s=="="){ press_equals(); return; }
        if(s=="x²"){ apply_square(); return; }
        if(s=="√"){  apply_sqrt();   return; }
        if(s=="÷") add_text("/");
        else if(s=="×") add_text("*");
        else add_text(s);
    }

    void add_text(const std::string& s){
        std::string cur = entry->value() ? entry->value() : "";
        cur += s;
        entry->value(cur.c_str());
        entry->insert_position((int)cur.size());
    }

    void do_backspace(){
        std::string cur = entry->value() ? entry->value() : "";
        if(cur.empty()) return;
        cur.erase(cur.size()-1);
        entry->value(cur.c_str());
        entry->insert_position((int)cur.size());
    }

    void press_equals(){
        std::string expr = entry->value() ? entry->value() : "";
        std::string err; double val=0.0;
        if(!evaluate(expr,val,err)){
            result->label("");
            history->label("");
            alert(err);
            return;
        }
        last_expr = trim(expr);
        last_value= val;
        std::string left = last_expr + "    =";
        history->label(left.c_str());
        std::string r = fmt12(val);
        result->label(r.c_str());
        entry->value(r.c_str());
        entry->insert_position((int)r.size());
        redraw();
    }

    void apply_square(){
        std::string cur = trim(entry->value()? entry->value() : "");
        if(cur.empty()){ alert("Enter a number first"); return; }
        std::string err; double v=0.0;
        if(!evaluate(cur,v,err)){ alert(err); return; }
        double r=v*v;
        if(!isFinite(r)){ alert("Error: overflow"); return; }
        std::string s=fmt12(r);
        entry->value(s.c_str());
        entry->insert_position((int)std::strlen(entry->value()));
    }

    void apply_sqrt(){
        std::string cur = trim(entry->value()? entry->value() : "");
        if(cur.empty()){ alert("Enter a number first"); return; }
        std::string err; double v=0.0;
        if(!evaluate(cur,v,err)){ alert(err); return; }
        if(v<0){ alert("Error: sqrt of negative"); return; }
        std::string s=fmt12(std::sqrt(v));
        entry->value(s.c_str());
        entry->insert_position((int)std::strlen(entry->value()));
    }

    int handle(int ev) FL_OVERRIDE {
        if(ev==FL_KEYDOWN){
            int k = Fl::event_key();
            if(k==FL_Enter || k==FL_KP_Enter){ press_equals(); return 1; }
            if(k==FL_Escape){ entry->value(""); result->label(""); history->label(""); return 1; }
            if(k==FL_BackSpace){ do_backspace(); return 1; }
        }
        return Fl_Window::handle(ev);
    }
};

int main(int argc, char** argv){
    try{
        App app(540, 520);
        app.show(argc, argv);
        return Fl::run();
    }catch(const std::exception& e){
        fl_alert("Fatal error: %s", e.what());
        return 2;
    }catch(...){
        fl_alert("Fatal error: unknown");
        return 3;
    }
}
