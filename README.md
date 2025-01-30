🎯 Quiz Application.


📌 Overview

This is a console-based quiz game written in C that allows users to:

Register and log in.
Choose a difficulty level: Beginner (B), Intermediate (I), or Pro (P).
Answer multiple-choice questions.
Track their scores and save them to a leaderboard.

📂 Project Structure

main.c – The core program that runs the quiz system.
questions.txt – Stores quiz questions, answers, and difficulty levels.
users.txt – Stores registered user credentials.
leaderboard.txt – Maintains user scores and rankings.

🛠 Features

✅ User Authentication – Register and log in before playing.
✅ Difficulty Levels – Choose from three levels: Beginner, Intermediate, or Pro.
✅ Randomized Questions – Questions are shuffled to enhance replayability.
✅ Scoring System – Tracks correct answers and saves scores to the leaderboard.
✅ Leaderboard Display – View top scores after playing.

📜 File Formats

Each line follows this format:
questions.txt

Question|Option1|Option2|Option3|Option4|Correct Answer|Difficulty
Example:
What is 2 + 2?|1|2|3|4|D|B
D – Correct answer (4th option).
B – Difficulty level (Beginner, Intermediate, Pro).

users.txt
Username|Password
Example:
john_doe|securepass123

leaderboard.txt
Username|Score|Difficulty
Example:
alice|10|Pro

🎮 How to Play

Register or log in.
Choose a difficulty level.
Answer up to 15 randomly selected questions.
View your final score and save it to the leaderboard.
Optionally, view the leaderboard or play again.

🎯 Additional Things that can be implemented in the Future

Implementing password encryption for security.
Using SQL as DataBase instead of Files
Add a GUI version using a graphical library.
Introduce timed questions to make the game more challenging.

                                                      THANK YOU!!
