#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 100

// Question structure
typedef struct {
    char question[MAX_LENGTH];
    char option1[MAX_LENGTH];
    char option2[MAX_LENGTH];
    char option3[MAX_LENGTH];
    char option4[MAX_LENGTH];
    char correctOption; // 'A', 'B', 'C', or 'D'
    char difficulty;    // 'B', 'I', or 'P'
} Question;

// Leaderboard structure
typedef struct {
    char username[MAX_LENGTH];
    int score;
    char difficulty[MAX_LENGTH];
} LeaderboardEntry;

// Function to load questions from file
int loadQuestions(Question *questions, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open questions file.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c|%c\n",
                  questions[count].question, questions[count].option1,
                  questions[count].option2, questions[count].option3,
                  questions[count].option4, &questions[count].correctOption,
                  &questions[count].difficulty) == 7) {
        count++;
    }

    fclose(file);
    return count;
}

// Function to save leaderboard entry to file
void saveLeaderboardEntry(const char *username, int score, const char *difficulty) {
    FILE *file = fopen("leaderboard.txt", "a");
    if (!file) {
        printf("Error: Could not open leaderboard file.\n");
        return;
    }

    fprintf(file, "%s|%d|%s\n", username, score, difficulty);
    fclose(file);
}

// Function to display the leaderboard
void displayLeaderboard() {
    FILE *file = fopen("leaderboard.txt", "r");
    if (!file) {
        printf("Error: Could not open leaderboard file.\n");
        return;
    }

    printf("\n--- Leaderboard ---\n");
    char username[MAX_LENGTH];
    int score;
    char difficulty[MAX_LENGTH];
    while (fscanf(file, "%[^|]|%d|%[^\n]\n", username, &score, difficulty) == 3) {
        printf("%s - Score: %d - Difficulty: %s\n", username, score, difficulty);
    }
    printf("--------------------\n");

    fclose(file);
}

// Function to register a user
void registerUser() {
    char username[MAX_LENGTH], password[MAX_LENGTH];
    printf("Enter a username: ");
    scanf("%s", username);
    printf("Enter a password: ");
    scanf("%s", password);

    FILE *file = fopen("users.txt", "a");
    if (!file) {
        printf("Error: Could not open users file.\n");
        return;
    }

    fprintf(file, "%s|%s\n", username, password);
    fclose(file);
    printf("Registration successful!\n");
}

// Function to log in a user
int loginUser(char *username) {
    char inputUsername[MAX_LENGTH], inputPassword[MAX_LENGTH];
    printf("Enter your username: ");
    scanf("%s", inputUsername);
    printf("Enter your password: ");
    scanf("%s", inputPassword);

    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printf("Error: Could not open users file.\n");
        return 0;
    }

    char storedUsername[MAX_LENGTH], storedPassword[MAX_LENGTH];
    while (fscanf(file, "%[^|]|%[^\n]\n", storedUsername, storedPassword) == 2) {
        if (strcmp(inputUsername, storedUsername) == 0 && strcmp(inputPassword, storedPassword) == 0) {
            strcpy(username, inputUsername);
            fclose(file);
            printf("Login successful!\n");
            return 1;
        }
    }

    fclose(file);
    printf("Invalid username or password.\n");
    return 0;
}

// Function to shuffle questions
void shuffleQuestions(Question *questions, int count) {
    srand(time(0));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Question temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

// Function to start the quiz
void startQuiz(Question *questions, int totalQuestions, char *username) {
    char difficulty;
    printf("Choose difficulty (B for Beginner, I for Intermediate, P for Pro): ");
    scanf(" %c", &difficulty);

    Question filteredQuestions[totalQuestions];
    int filteredCount = 0;

    // Filter questions based on difficulty
    for (int i = 0; i < totalQuestions; i++) {
        if (questions[i].difficulty == difficulty) {
            filteredQuestions[filteredCount++] = questions[i];
        }
    }

    if (filteredCount == 0) {
        printf("No questions available for the chosen difficulty.\n");
        return;
    }

    shuffleQuestions(filteredQuestions, filteredCount);

    int score = 0;
    char answer;
    int questionsToDisplay = filteredCount < 15 ? filteredCount : 15;

    for (int i = 0; i < questionsToDisplay; i++) {
        printf("Q%d: %s\n", i + 1, filteredQuestions[i].question);
        printf("A. %s\n", filteredQuestions[i].option1);
        printf("B. %s\n", filteredQuestions[i].option2);
        printf("C. %s\n", filteredQuestions[i].option3);
        printf("D. %s\n", filteredQuestions[i].option4);
        printf("Enter your answer (A/B/C/D): ");
        getchar(); // Consume leftover newline character
        scanf("%c", &answer);
        if (answer == filteredQuestions[i].correctOption) {
            score++;
        }
    }
    printf("Quiz finished! Your score: %d/%d\n", score, questionsToDisplay);

    // Save score to leaderboard
    char difficultyName[MAX_LENGTH];
    if (difficulty == 'B')
        strcpy(difficultyName, "Beginner");
    else if (difficulty == 'I')
        strcpy(difficultyName, "Intermediate");
    else
        strcpy(difficultyName, "Pro");

    saveLeaderboardEntry(username, score, difficultyName);

    // Add View Leaderboard and Play Again options
    int choice;
    printf("\nWhat would you like to do next?\n");
    printf("1. View Leaderboard\n");
    printf("2. Play Again\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        displayLeaderboard();
    } else if (choice == 2) {
        startQuiz(questions, totalQuestions, username);
    } else {
        printf("Thank you for playing! Goodbye!\n");
    }
}

// Main function
int main() {
    Question questions[MAX_LENGTH];
    int totalQuestions = loadQuestions(questions, "questions.txt");
    if (totalQuestions == 0) {
        return 1;
    }

    char username[MAX_LENGTH];
    int loggedIn = 0;

    while (!loggedIn) {
        int choice;
        printf("\n1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            loggedIn = loginUser(username);
        } else {
            printf("Goodbye!\n");
            return 0;
        }
    }

    startQuiz(questions, totalQuestions, username);

    return 0;
}
