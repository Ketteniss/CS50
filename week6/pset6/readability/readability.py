#   Write a programm that takes text input by the user and
#   gives that text a grade level after the Coleman-Liau formula
from cs50 import get_string

# Get text from user
istr = get_string("Text: ")

# Initialize counters
wCount = 1
sCount = 0
lCount = 0

# Traverse text
for c in istr:

    # Count letters
    if (c.isalpha()):
        lCount += 1

    # Count words
    if (c == " "):
        wCount += 1

    # Count sentences of text
    if (c in [".", "?", "!"]):
        sCount += 1

# L is the average number of letters per 100 words in the text
L = (lCount / wCount) * 100

# S is the average number of sentences per 100 words in the text
S = (sCount / wCount) * 100

# Calculate grade level using the Coleman-Liau formula
index = 0.0588 * L - 0.296 * S - 15.8

# Print letter and sentence count aswell as grade level of text
result = ""
if (index < 1): result = "Before Grade 1"
else:
    index = round(index)
    result = f"Grade {index}"
    if (index > 16): result = "Grade 16+"
print(result)