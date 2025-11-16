#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cctype>
#include <random>
#include <ctime>

static std::string lower(std::string s){ for(char &c: s) c = (char)std::tolower((unsigned char)c); return s; }
static std::string trim(const std::string& s){ size_t a=s.find_first_not_of(" \t\r\n"); if(a==std::string::npos) return ""; size_t b=s.find_last_not_of(" \t\r\n"); return s.substr(a,b-a+1); }
static bool alpha_only(const std::string& s){ if(s.empty()) return false; for(char c: s) if(!std::isalpha((unsigned char)c)) return false; return true; }

struct Category { std::string name; std::vector<std::string> words; };

static const std::vector<Category> CATS = {
    {"Animals",   {"elephant","giraffe","kangaroo","dolphin","cheetah","penguin","hamster","alligator","butterfly","tortoise","squirrel","rabbit","owl","octopus"}},
    {"Fruits",    {"apple","banana","orange","pineapple","strawberry","blueberry","mango","watermelon","papaya","grapefruit","peach","pear","kiwi","lemon","lime"}},
    {"Countries", {"rwanda","kenya","uganda","tanzania","ethiopia","nigeria","ghana","canada","brazil","argentina","mexico","spain","france","germany","japan","china","india","italy","sweden","norway"}},
    {"Movies",    {"inception","interstellar","avatar","gladiator","parasite","matrix","titanic","amadeus","rocky","coco","arrival","whiplash","joker","dune","skyfall"}},
    {"Books",     {"dune","foundation","dracula","hamlet","odyssey","iliad","emma","matilda","persuasion","siddhartha","inferno","ulysses","beowulf"}},
    {"Teams",     {"lakers","warriors","celtics","patriots","yankees","dodgers","arsenal","barcelona","chelsea","liverpool","juventus","psg","bayern","realmadrid"}}
};

static std::mt19937& rng(){
    static std::mt19937 gen((unsigned)std::chrono::high_resolution_clock::now().time_since_epoch().count());
    return gen;
}

static int pick_index(int n){
    std::uniform_int_distribution<int> dist(0, n-1);
    return dist(rng());
}

static std::string mask_word(const std::string& secret, const std::set<char>& correct){
    std::string m; m.reserve(secret.size());
    for(char c: secret){
        if(std::isalpha((unsigned char)c)){
            char lc = (char)std::tolower((unsigned char)c);
            m.push_back(correct.count(lc) ? c : '_');
        } else {
            m.push_back(c);
        }
    }
    return m;
}

static bool all_revealed(const std::string& secret, const std::set<char>& correct){
    for(char c: secret){
        if(std::isalpha((unsigned char)c)){
            if(!correct.count((char)std::tolower((unsigned char)c))) return false;
        }
    }
    return true;
}

int main(){
    std::cout << "=== Word Guess (Terminal) ===\n";
    for(;;){
        std::cout << "\nChoose a category:\n";
        for(size_t i=0;i<CATS.size();++i) std::cout << "  " << (i+1) << ") " << CATS[i].name << "\n";
        std::cout << "Enter number (or type 'exit'): ";
        std::string line; if(!std::getline(std::cin, line)) return 0;
        line = trim(lower(line));
        if(line=="exit") return 0;
        if(line.empty()) continue;
        int ci = -1;
        try { ci = std::stoi(line) - 1; } catch(...) { ci = -1; }
        if(ci<0 || ci>=(int)CATS.size()){ std::cout << "Invalid choice.\n"; continue; }

        const auto& words = CATS[ci].words;
        std::string secret = words[pick_index((int)words.size())];
        std::set<char> correct, wrong;
        int maxChances = 6;
        int left = maxChances;

        std::cout << "\nCategory: " << CATS[ci].name << "\n";
        std::cout << "Type a letter, a whole word, or 'exit' to quit.\n";
        std::cout << "You have " << left << " wrong guesses allowed.\n";

        for(;;){
            std::string masked = mask_word(secret, correct);
            std::cout << "\nWord: " << masked << "\n";
            std::cout << "Chances left: " << left << "  |  Guessed: ";
            if(correct.empty() && wrong.empty()) std::cout << "(none)";
            else {
                for(char c: correct) std::cout << c << ' ';
                if(!wrong.empty()){ std::cout << "| "; for(char c: wrong) std::cout << c << ' '; }
            }
            std::cout << "\nGuess: ";
            if(!std::getline(std::cin, line)) return 0;
            line = trim(line);
            if(line.empty()) continue;
            std::string lline = lower(line);

            if(lline=="exit") { std::cout << "Bye!\n"; return 0; }

            if(lline.size()==1 && std::isalpha((unsigned char)lline[0])){
                char g = lline[0];
                if(correct.count(g) || wrong.count(g)){
                    std::cout << "Already tried '" << g << "'.\n";
                    continue;
                }
                bool hit=false;
                for(char c: secret) if((char)std::tolower((unsigned char)c)==g){ hit=true; break; }
                if(hit){
                    correct.insert(g);
                    if(all_revealed(secret, correct)){
                        std::cout << "\nWord: " << mask_word(secret, correct) << "\n";
                        std::cout << "You win! The word was: " << secret << "\n";
                        break;
                    }
                }else{
                    wrong.insert(g);
                    --left;
                    if(left<=0){
                        std::cout << "Out of chances. The word was: " << secret << "\n";
                        break;
                    }
                }
                continue;
            }

            if(alpha_only(lline)){
                if(lline==secret){
                    for(char c: secret){
                        if(std::isalpha((unsigned char)c)){
                            correct.insert((char)std::tolower((unsigned char)c));
                        }
                    }
                    std::cout << "\nWord: " << mask_word(secret, correct) << "\n";
                    std::cout << "You win! The word was: " << secret << "\n";
                    break;
                } else {
                    --left;
                    std::cout << "Wrong word guess.\n";
                    if(left<=0){
                        std::cout << "Out of chances. The word was: " << secret << "\n";
                        break;
                    }
                    continue;
                }
            }

            std::cout << "Enter a single letter, a whole word, or 'exit'.\n";
        }

        for(;;){
            std::cout << "\nPlay again? (y/n): ";
            if(!std::getline(std::cin, line)) return 0;
            line = lower(trim(line));
            if(line=="y" || line=="yes") break;
            if(line=="n" || line=="no"){ std::cout << "Goodbye!\n"; return 0; }
        }
    }
}
