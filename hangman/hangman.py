from curses.ascii import isalpha
import random
import urllib.request
from printhangman import *

response = urllib.request.urlopen("https://www.mit.edu/~ecprice/wordlist.10000")
word_list = response.read().decode().splitlines()

def generate_word(word_list):
	word = random.choice(word_list)
	return (word)

def check_guess(word, guess, guesses_left, wordprint):
	if guess not in word:
		guesses_left -= 1
		print("Incorrect guess: %d remaining" % guesses_left)
		return (guesses_left, wordprint)
	for i in range(0, len(word)):
		if word[i] == guess[0]:
			pythonisdumb = list(wordprint)
			pythonisdumb[i] = guess[0]
			wordprint = ''.join(pythonisdumb)
	print("Correct!")
	return (guesses_left, wordprint)


print("Let's play Hangman")
word = generate_word(word_list)
wordprint = ("_" * len(word))
print("Your word: ", wordprint)

guesses_left = 6
guesses = []

while True:
	guess = input("->  ").lower()
	if guess == "exit":
		break
	if guess in guesses:
		print("Already guessed")
	else:
		if guess.isalpha() and (len(guess) == 1):
			guesses_left , wordprint = check_guess(word, guess, guesses_left, wordprint)
			guesses.append(guess)
		else:
			print("Not a valid guess")
	if guesses_left == 0:
		printhangman(guesses_left)
		print("No more guesses, you lose!")
		print("Your word was", word)
		break
	printhangman(guesses_left)
	print("\n\nYour guesses", guesses)
	print(wordprint)
	if '_' not in wordprint:
		print("You successfully guessed the word, good job, you win!")
		break

print("Thanks for playing")