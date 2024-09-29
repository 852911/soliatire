#include <iostream>
#include <windows.h>
#include <stack>
#include <array>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <sstream>
#include <cctype>


using namespace std;
void setConsoleColor(WORD color)
{
    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

class Card
{
    string suit;
    int rank;
    bool faceUp;
public:
    Card(string s = "", int r = 0, bool f = false)
    {
        suit = s;
        rank = r;
        faceUp = f;
    }
    void toggleFace()
    {
        faceUp = !faceUp;
    }
    friend ostream& operator<<(ostream& os, const Card& card) {
        if (card.faceUp) {
            os << card.rank << " of " << card.suit; // Display rank and suit
        }
        else {
            os << "XX"; // Display "XX" for face-down cards
        }
        return os;
    }

    bool canBePlacedOn(const Card& obj) const
    {

        bool isThisRed = (this->suit == "Heart" || this->suit == "Diamond");


        bool isObjRed = (obj.suit == "Heart" || obj.suit == "Diamond");


        return (this->rank == obj.rank - 1) && (isThisRed != isObjRed);
    }


    bool isFaceUp()const { return faceUp; }
    int getRank()const { return rank; }
    string getSuit()const { return suit; }


    void printCard() const
    {
        // Get console handle to change text color
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

        if (faceUp == false)
        {
            cout << "[***]";
        }
        else if (faceUp == true)
        {
            // Convert rank to string (A for Ace, J for Jack, etc.)
            string rankStr = to_string(rank);
            if (rank == 1) rankStr = "A";  // Ace
            else if (rank == 11) rankStr = "J"; // Jack
            else if (rank == 12) rankStr = "Q"; // Queen
            else if (rank == 13) rankStr = "K"; // King

            SetConsoleOutputCP(CP_UTF8);  // Set console to UTF-8 for Unicode support

            // Printing the card suit with colors
            if (suit == "Heart")
            {
                // Set red color for Hearts
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "[" << rankStr << " " << "\u2665" << "]"; // ♥ symbol for Heart
            }
            else if (suit == "Diamond")
            {
                // Set red color for Diamonds
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << "[" << rankStr << " " << "\u2666" << "]"; // ♦ symbol for Diamond
            }
            else if (suit == "Spade")
            {
                // Set grey/black (default) for Spades
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "[" << rankStr << " " << "\u2660" << "]"; // ♠ symbol for Spade
            }
            else if (suit == "Club")
            {
                // Set grey/black (default) for Clubs
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                cout << "[" << rankStr << " " << "\u2663" << "]"; // ♣ symbol for Club
            }

            // Reset to default console color after printing
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
    }


};


template<typename T>
class List
{
private:
    class Node
    {
    public:
        T data;
        Node* next;
        Node* prev;
        Node(T c)
        {
            data = c;
            next = prev = nullptr;
        }
    };
    Node* head;
    Node* tail;
    int size;
public:
    List()
    {
        head = tail = nullptr;
        size = 0;
    }
    ~List() {
        clear();
    }
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }
    void push(const T& value)
    {
        Node* nod = new Node(value);
        nod->prev = tail;
        nod->next = nullptr;

        if (tail != nullptr) {
            tail->next = nod;
        }
        else {
            head = nod;  // If list is empty, head becomes the new node
        }

        tail = nod;  // Update tail to the new node
        size++;  // Increment size of the list
    }
    T& at(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        Node* current = head;
        for (int i = 0; i < index; i++){
            current = current->next;
        }
        return current->data;
    }
    T pop() {
        if (tail == nullptr) {
            throw out_of_range("List is empty");
        }
        Node* oldTail = tail;
        T value = tail->data;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete oldTail;
        --size;
        return value;
    }
    int getSize() const {
        return size;
    }
    bool isEmpty() const {
        return size == 0;
    }
    void printAllCards() const {
        Node* current = head;  // Start from the head
        if (isEmpty()) {
            std::cout << "[empty]";  // Print only when the column is completely empty
            std::cout << std::endl;  // New line after printing
            return;
        }

        while (current != nullptr) {  // Iterate through all nodes
            current->data.printCard();  // Call printCard on the data
            std::cout << " ";  // Space between cards
            current = current->next;  // Move to the next node
        }

        std::cout << std::endl;  // New line after printing all cards
    }


};


template<typename T>
class Stack
{
private:
    class Node {
    public:
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };
    Node* topNode;
    int size;
public:
    Stack() : topNode(nullptr), size(0) {}

    ~Stack() {
        clear();
    }
    void push(const T& value)
    {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        ++size;
    }
    T pop() {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        Node* oldTop = topNode;
        T value = topNode->data;
        topNode = topNode->next;
        delete oldTop;
        --size;
        return value;
    }
    T& top() const {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return topNode->data;
    }
    bool isEmpty() const
    {
        return size == 0;
    }

    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
    int getSize() const {
        return size;
    }
};

class Deck {
    vector<Card> cards;

public:
    Deck() {
        initializeDeck();
        shuffle();
    }

    void initializeDeck()
    {
        string suits[] = { "Heart", "Diamond", "Club", "Spade" };
        for (const string& suit : suits)
        {
            for (int rank = 1; rank <= 13; ++rank)
            {
                cards.push_back(Card(suit, rank, false)); // Use emplace_back for efficiency
            }
        }
    }

    void shuffle()
    {
        auto seed = chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(cards.begin(), cards.end(), default_random_engine(seed)); // Ensure std:: before shuffle
    }

    bool empty() const {
        return cards.empty();
    }

    Card draw() {
        if (empty()) throw out_of_range("Deck is empty");
        Card topCard = cards.back();
        cards.pop_back();
        return topCard;
    }

    void printDeck() const {
        for (const auto& card : cards) {
            card.printCard();
            cout << endl;
        }
    }

};

class Command
{
public:
    char commandType;
    char sourceType;
    int sourceIndex;
    char destinationType;
    int destinationIndex;
    int numCards;

    Command() : commandType(' '), sourceType(' '), sourceIndex(0), destinationType(' '), destinationIndex(0), numCards(0) {}
};


class Game {
    Stack<Card> stockPile;
    Stack<Card> wastePile;
    Stack<Command> undoStack;
    Stack<Card> foundation[4];
    List<Card> tableau[7];
    bool gameOver;
    int totalMoves;

public:
    Game() : gameOver(false), totalMoves(0)
    {
        initializeGame();
    }

    void initializeGame()
    {
        Deck deck;
        // Place cards in tableau
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j <= i; j++) {
                Card drawn = deck.draw();
                if (i == j) {
                    drawn.toggleFace(); // Flip the last card face up
                }
                tableau[i].push(drawn);
            }
        }

        // Place remaining cards in stockPile
        while (!deck.empty())
        {
            stockPile.push(deck.draw());
        }

        // Flip the top card of the stockPile face up
        if (!stockPile.isEmpty()) {
            Card topCard = stockPile.top();
            topCard.toggleFace();
            stockPile.pop();
            stockPile.push(topCard);
        }
    }

    void printGameState() {
        cout << "Stock       Waste" << "                      "
            << "Foundation1" << "     " << "Foundation2" << "     "
            << "Foundation3" << "     " << "Foundation4" << endl;

        // Print Stock

        if (!stockPile.isEmpty()) {
            stockPile.top().printCard();
        }
        else {
            cout << "[   ]";
        }
        cout << "       ";

        // Print Waste
        if (!wastePile.isEmpty()) {
            wastePile.top().printCard();
        }
        else {
            cout << "[   ]";
        }
        cout << "                        ";

        // Print Foundations
        for (int i = 0; i < 4; i++)
        {
            if (!foundation[i].isEmpty())
            {
                foundation[i].top().printCard();
            }
            else {
                cout << "[    ]";
            }
            cout << "          ";
        }
        cout << endl;
        cout <<" " << stockPile.getSize() << "          " << wastePile.getSize() << endl;
        cout << "\n\n\n\n\n                                               Tableau\n\n\n\n\n";
        int maxHeight = getMaxHeight();

        // Print Tableau
        for (int row = 0; row < maxHeight; row++) {
            for (int col = 0; col < 7; col++) {
                if (row < tableau[col].getSize()) {
                    tableau[col].at(row).printCard(); // Print the card at the current row for this column
                }
                else {
                    cout << "     "; // Print space if there's no card
                }
                cout << "             "; // Space between columns
            }
            cout << endl; // New line after printing all columns in this row
        }
    }

    void runGame() {
        string input;
        while (!gameOver)
        {
            try {
                printGameState();
                cout << "Enter command: ";
                getline(cin, input);
                Command cmd = parseCommand(input);
                processCommand(cmd);
            }
            catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << endl;
                cout << "Invalid command. Please try again." << endl;
            }
            catch (const out_of_range& e) {
                cout << "Error: " << e.what() << endl;
                cout << "Invalid command. Please try again." << endl;
            }
            catch (const exception& e) {
                cout << "An unexpected error occurred: " << e.what() << endl;
                cout << "Please try again." << endl;
            }
        }
    }
    Command parseCommand(const string& input)
    {
        Command cmd;
        istringstream iss(input);
        string token;

        if (!(iss >> token)) {
            throw invalid_argument("Empty command");
        }

        // Convert to lowercase for case-insensitive comparison
        transform(token.begin(), token.end(), token.begin(), ::tolower);

        if (token == "move" || token == "m")
        {
            cmd.commandType = 'm';

            // Parse source
            if (!(iss >> token))
            {
                throw invalid_argument("Missing source");
            }
            if (token.length() != 2 ||
                (token[0] != 't' && token[0] != 'w' && token[0] != 'f') ||
                !isdigit(token[1])) {
                throw invalid_argument("Invalid source: " + token);
            }
            cmd.sourceType = token[0];
            cmd.sourceIndex = token[1] - '0' - 1; // Convert to 0-based index

            // Parse destination
            if (!(iss >> token)) {
                throw invalid_argument("Missing destination");
            }
            if (token.length() != 2 ||
                (token[0] != 't' && token[0] != 'f') ||
                !isdigit(token[1])) {
                throw invalid_argument("Invalid destination: " + token);
            }
            cmd.destinationType = token[0];
            cmd.destinationIndex = token[1] - '0' - 1; // Convert to 0-based index

            // Parse number of cards (optional)
            if (iss >> cmd.numCards) {
                if (cmd.numCards <= 0) {
                    throw invalid_argument("Invalid number of cards: " + to_string(cmd.numCards));
                }
            }
            else {
                cmd.numCards = 1; // Default to 1 if not specified
            }
        }
        else if (token == "draw" || token == "d") {
            cmd.commandType = 'd';
        }
        else if (token == "undo" || token == "u") {
            cmd.commandType = 'u';
        }
        else {
            throw invalid_argument("Invalid command: " + token);
        }

        return cmd;
    }
    int getMaxHeight()
    {
        int maxHeight = 0;
        for (int i = 0; i < 7; i++) {
            if (tableau[i].getSize() > maxHeight) {
                maxHeight = tableau[i].getSize();
            }
        }
        return maxHeight;
    }
    

   
    void processCommand(const Command& cmd)
    {
        switch (cmd.commandType) 
        {
        case 'm':
            moveCards(cmd);
            break;
        case 'd':
            drawCardFromStock();
            break;
        case 'u':
            undoLastMove();
            break;
        default:
            throw invalid_argument("Invalid command type");
        }
    }
    void drawCardFromStock()
    {
        if (!stockPile.isEmpty())
        {
            Card drawnCard = stockPile.top();
            stockPile.pop();

            // Toggle face up when adding to waste pile
            drawnCard.toggleFace();
            wastePile.push(drawnCard);

            // Create and push a command to the undo stack
            Command drawCommand;
            drawCommand.commandType = 'd';
            undoStack.push(drawCommand);

            totalMoves++; // Increment the total number of moves
        }
        else if (!wastePile.isEmpty())
        {
            // Move all cards from wastePile to stockPile and make them face down
            while (!wastePile.isEmpty())
            {
                Card card = wastePile.top();
                wastePile.pop();

                // Ensure all cards are face down in stockPile
                if (card.isFaceUp())
                {
                    card.toggleFace();
                }
                stockPile.push(card);
            }

            // Create and push a reset command to the undo stack
            Command resetCommand;
            resetCommand.commandType = 'r'; // 'r' for reset
            undoStack.push(resetCommand);

            totalMoves++; // Increment the total number of moves
        }
        else
        {
            cout << "Both stock and waste piles are empty!" << endl;
        }

        // Toggle the face of the top card in the waste pile if not empty
        if (!wastePile.isEmpty())
        {
            if (!wastePile.top().isFaceUp())
            {
                wastePile.top().toggleFace();
            }
        }
    }



    bool isValidMove(const Card& sourceCard, char destinationType, List<Card>* destinationList, Stack<Card>* destinationStack) {
        if (destinationType == 't') {
            if (destinationList->isEmpty()) {
                return (sourceCard.getRank() == 13); // Only King can be placed on empty tableau
            }
            else {
                return sourceCard.canBePlacedOn(destinationList->at(destinationList->getSize() - 1));
            }
        }
        else if (destinationType == 'f') {
            if (destinationStack->isEmpty()) {
                return (sourceCard.getRank() == 1); // Only Ace can be placed on empty foundation
            }
            else {
                Card& topFoundationCard = destinationStack->top();
                return (sourceCard.getSuit() == topFoundationCard.getSuit() &&
                    sourceCard.getRank() == topFoundationCard.getRank() + 1);
            }
        }
        return false; // Invalid destination type
    }

    void moveCards(const Command& cmd)
    {
        Card sourceCard;
        List<Card>* sourceList = nullptr;
        Stack<Card>* sourceStack = nullptr;
        List<Card>* destinationList = nullptr;
        Stack<Card>* destinationStack = nullptr;

        // Determine the source of the cards
        if (cmd.sourceType == 't') {
            if (cmd.sourceIndex < 0 || cmd.sourceIndex >= 7 || tableau[cmd.sourceIndex].isEmpty()) {
                throw invalid_argument("Invalid source tableau");
            }
            sourceList = &tableau[cmd.sourceIndex];
            if (cmd.numCards > sourceList->getSize()) {
                throw invalid_argument("Not enough cards in source tableau");
            }
            sourceCard = sourceList->at(sourceList->getSize() - cmd.numCards);
            if (!sourceCard.isFaceUp()) {
                throw invalid_argument("Source card is face down");
            }
        }
        else if (cmd.sourceType == 'w') {
            if (wastePile.isEmpty()) {
                throw invalid_argument("Waste pile is empty");
            }
            sourceStack = &wastePile;
            sourceCard = sourceStack->top();
            if (cmd.numCards != 1) {
                throw invalid_argument("Can only move one card from waste pile");
            }
        }
        else if (cmd.sourceType == 'f') {
            if (cmd.sourceIndex < 0 || cmd.sourceIndex >= 4 || foundation[cmd.sourceIndex].isEmpty()) {
                throw invalid_argument("Invalid source foundation");
            }
            sourceStack = &foundation[cmd.sourceIndex];
            sourceCard = sourceStack->top();
            if (cmd.numCards != 1) {
                throw invalid_argument("Can only move one card from foundation");
            }
        }
        else {
            throw invalid_argument("Invalid source type");
        }

        // Determine the destination for the cards
        if (cmd.destinationType == 't') {
            if (cmd.destinationIndex < 0 || cmd.destinationIndex >= 7) {
                throw invalid_argument("Invalid destination tableau");
            }
            destinationList = &tableau[cmd.destinationIndex];
        }
        else if (cmd.destinationType == 'f') {
            if (cmd.destinationIndex < 0 || cmd.destinationIndex >= 4) {
                throw invalid_argument("Invalid destination foundation");
            }
            destinationStack = &foundation[cmd.destinationIndex];
            if (cmd.numCards != 1) {
                throw invalid_argument("Can only move one card to foundation");
            }
        }
        else {
            throw invalid_argument("Invalid destination type");
        }

        bool validMove = isValidMove(sourceCard, cmd.destinationType, destinationList, destinationStack);

        if (!validMove) {
            throw invalid_argument("Invalid move");
        }

        // Perform the move
        List<Card> tempList;
        for (int i = 0; i < cmd.numCards; i++) {
            Card card = (sourceList) ? sourceList->at(sourceList->getSize() - cmd.numCards + i) : sourceStack->top();
            tempList.push(card);
        }

        // Remove cards from source
        for (int i = 0; i < cmd.numCards; i++) {
            if (sourceList) {
                sourceList->pop();
            }
            else {
                sourceStack->pop();
            }
        }

        // Add cards to destination
        for (int i = 0; i < cmd.numCards; i++) {
            Card card = tempList.at(i);
            if (destinationList) {
                destinationList->push(card);
            }
            else {
                destinationStack->push(card);
            }
        }

        // If moving from tableau, flip the new top card if it's face down
        if (cmd.sourceType == 't' && !sourceList->isEmpty()) {
            Card& newTopCard = sourceList->at(sourceList->getSize() - 1);
            if (!newTopCard.isFaceUp()) {
                newTopCard.toggleFace();
            }
        }

        // Add move to undo stack
        undoStack.push(cmd);
        totalMoves++;

        // Check for game completion
        checkGameCompletion();
    }


    void checkGameCompletion() {
        bool allFoundationsFull = true;
        bool validMovesExist = false;

        // Check if all foundation piles have 13 cards each
        for (int i = 0; i < 4; i++) {
            if (foundation[i].getSize() != 13) {
                allFoundationsFull = false;
                break;
            }
        }

        if (allFoundationsFull) {
            gameOver = true;
            cout << "Congratulations! You've won the game in " << totalMoves << " moves!" << endl;
            return;
        }

        // Check for valid moves
        // From tableau to tableau
        for (int i = 0; i < 7; i++) {
            if (tableau[i].isEmpty()) continue;
            Card sourceCard = tableau[i].at(tableau[i].getSize() - 1);
            for (int j = 0; j < 7; j++) {
                if (i == j) continue;
                if (tableau[j].isEmpty()) {
                    if (sourceCard.getRank() == 13) { // King can be moved to empty tableau
                        validMovesExist = true;
                        return;
                    }
                }
                else {
                    Card destCard = tableau[j].at(tableau[j].getSize() - 1);
                    if (sourceCard.canBePlacedOn(destCard)) {
                        validMovesExist = true;
                        return;
                    }
                }
            }
        }

        // From tableau to foundation
        for (int i = 0; i < 7; i++) {
            if (tableau[i].isEmpty()) continue;
            Card sourceCard = tableau[i].at(tableau[i].getSize() - 1);
            for (int j = 0; j < 4; j++) {
                if (foundation[j].isEmpty()) {
                    if (sourceCard.getRank() == 1) { // Ace can be moved to empty foundation
                        validMovesExist = true;
                        return;
                    }
                }
                else {
                    Card topFoundationCard = foundation[j].top();
                    if (sourceCard.getSuit() == topFoundationCard.getSuit() &&
                        sourceCard.getRank() == topFoundationCard.getRank() + 1) {
                        validMovesExist = true;
                        return;
                    }
                }
            }
        }

        // From waste pile to tableau or foundation
        if (!wastePile.isEmpty()) {
            Card wasteCard = wastePile.top();
            // Check tableau
            for (int i = 0; i < 7; i++) {
                if (tableau[i].isEmpty()) {
                    if (wasteCard.getRank() == 13) { // King can be moved to empty tableau
                        validMovesExist = true;
                        return;
                    }
                }
                else {
                    Card destCard = tableau[i].at(tableau[i].getSize() - 1);
                    if (wasteCard.canBePlacedOn(destCard)) {
                        validMovesExist = true;
                        return;
                    }
                }
            }
            // Check foundation
            for (int i = 0; i < 4; i++) {
                if (foundation[i].isEmpty()) {
                    if (wasteCard.getRank() == 1) { // Ace can be moved to empty foundation
                        validMovesExist = true;
                        return;
                    }
                }
                else {
                    Card topFoundationCard = foundation[i].top();
                    if (wasteCard.getSuit() == topFoundationCard.getSuit() &&
                        wasteCard.getRank() == topFoundationCard.getRank() + 1) {
                        validMovesExist = true;
                        return;
                    }
                }
            }
        }

        // Check if stock pile is not empty
        if (!stockPile.isEmpty()) {
            validMovesExist = true;
            return;
        }

        // If we've reached here, no valid moves exist
        if (!validMovesExist) {
            gameOver = true;
            cout << "Game over! No more valid moves. You made " << totalMoves << " moves." << endl;
        }
    }


    void undoLastMove() {
        if (undoStack.isEmpty()) {
            cout << "No moves to undo." << endl;
            return;
        }

        Command lastCommand = undoStack.pop();
        switch (lastCommand.commandType) {
        case 'm': {
            // Undo move command
            List<Card>* sourceList = nullptr;
            Stack<Card>* sourceStack = nullptr;
            List<Card>* destinationList = nullptr;
            Stack<Card>* destinationStack = nullptr;

            // Determine source and destination (reversed from original move)
            if (lastCommand.destinationType == 't') {
                sourceList = &tableau[lastCommand.destinationIndex];
            }
            else if (lastCommand.destinationType == 'f') {
                sourceStack = &foundation[lastCommand.destinationIndex];
            }

            if (lastCommand.sourceType == 't') {
                destinationList = &tableau[lastCommand.sourceIndex];
            }
            else if (lastCommand.sourceType == 'w') {
                destinationStack = &wastePile;
            }
            else if (lastCommand.sourceType == 'f') {
                destinationStack = &foundation[lastCommand.sourceIndex];
            }

            // Move cards back
            List<Card> tempList;
            for (int i = 0; i < lastCommand.numCards; i++) {
                Card card = (sourceList) ? sourceList->pop() : sourceStack->pop();
                tempList.push(card);
            }

            // Restore cards to their original position
            for (int i = lastCommand.numCards - 1; i >= 0; i--) {
                Card card = tempList.at(i);
                if (destinationList) {
                    destinationList->push(card);
                }
                else {
                    destinationStack->push(card);
                }
            }

            // If moved from tableau, handle the face-up/face-down state of the previous top card
            if (lastCommand.sourceType == 't' && !destinationList->isEmpty()) {
                int size = destinationList->getSize();
                if (size > lastCommand.numCards) {
                    Card& previousTopCard = destinationList->at(size - lastCommand.numCards - 1);
                    if (previousTopCard.isFaceUp()) {
                        previousTopCard.toggleFace();
                    }
                }
            }
            break;
        }
        case 'd':
            // Undo draw command
            if (!wastePile.isEmpty()) {
                Card card = wastePile.pop();
                card.toggleFace(); // Make it face down
                stockPile.push(card);
            }
            break;
        case 'r':
            // Undo reset command (moving cards from stock back to waste)
            while (!stockPile.isEmpty()) {
                Card card = stockPile.pop();
                card.toggleFace(); // Make it face up
                wastePile.push(card);
            }
            break;
        }

        totalMoves--;
    }


    
};











int main()
{
    Game sol;
    sol.runGame();




    return 0;
}