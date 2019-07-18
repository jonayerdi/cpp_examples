#include <iostream>
#include <string>
#include <exception>
#include <unordered_set>

using namespace std;

class GuessWord 
{
    private:
        const string word;
        unordered_set<char> letters;
        unordered_set<char> guessed;
        unsigned attempts;
    public:
        GuessWord(const string word, unsigned attempts) : word(word), letters(), guessed(), attempts(attempts)
        {
            for(char letter : word) {
                letters.insert(letter);
            }
        }
        GuessWord(const string word) : GuessWord(word, 3)
        {}
        friend ostream& operator<<(ostream& os, const GuessWord& obj) {
            for(char letter : obj.word) {
                if(obj.guessed.find(letter) != obj.guessed.end()) {
                    os << letter;
                } else {
                    os << '_';
                }
            }
            return os;
        }
        const string& getWord() {
            return this->word;
        }
        unsigned getAttempts() {
            return this->attempts;
        }
        bool isGuessed() {
            for(char letter : letters) {
                if(guessed.find(letter) == guessed.end()) {
                    return false;
                }
            }
            return true;
        }
        bool guessLetter(char letter) {
            if(attempts == 0) {
                throw exception{}; // Should have checked before
            }
            if(guessed.insert(letter).second) {
                if(letters.find(letter) == letters.end()) {
                   --attempts;
                }
                return true;
            } else {
                return false;
            }
        }
};

int main()
{
    GuessWord word {"sausage"};
    char guess;
    // Game loop
    while(word.getAttempts() > 0) {
        cout << "Guessed word: " << word << endl;
        cout << "Attempts left: " << word.getAttempts() << endl;
        cout << "Guess a letter: "; cout.flush();
        cin >> guess;
        if(!word.guessLetter(guess)) {
            cout << "You already guessed that letter" << endl << endl;
        } else {
            cout << endl;
            if(word.isGuessed()) {
                break;
            }
        }
    }
    // Win condition
    if(word.isGuessed()) {
        cout << word.getWord() << endl;
        cout << "You win :)" << endl;
    } else {
        cout << "You lose :(" << endl;
    }
}
