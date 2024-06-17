"""Typing test implementation"""
from typing import OrderedDict

from utils import *
from ucb import main, interact, trace
from datetime import datetime


###########
# Phase 1 #
###########


def choose(paragraphs, select, k):
    """Return the Kth paragraph from PARAGRAPHS for which SELECT called on the
    paragraph returns true. If there are fewer than K such paragraphs, return
    the empty string.
    """
    # BEGIN PROBLEM 1
    i = 0
    chosen_paragraph = ''
    for paragraph in paragraphs:
        if select(paragraph):
            if i == k:
                chosen_paragraph = paragraph
                break
            i += 1
    return chosen_paragraph
    # END PROBLEM 1


def about(topic):
    """Return a select function that returns whether a paragraph contains one
    of the words in TOPIC.

    >>> about_dogs = about(['dog', 'dogs', 'pup', 'puppy'])
    >>> choose(['Cute Dog!', 'That is a cat.', 'Nice pup!'], about_dogs, 0)
    'Cute Dog!'
    >>> choose(['Cute Dog!', 'That is a cat.', 'Nice pup.'], about_dogs, 1)
    'Nice pup.'
    """
    assert all([lower(x) == x for x in topic]), 'topics should be lowercase.'
    # BEGIN PROBLEM 2
    def select(paragraph):
        words = split(lower(remove_punctuation(paragraph)))
        words_in = 0
        for a_word in words:
            if a_word in topic:
                words_in += 1
        return words_in != 0
    return select
    # END PROBLEM 2


def accuracy(typed, reference):
    """Return the accuracy (percentage of words typed correctly) of TYPED
    when compared to the prefix of REFERENCE that was typed.

    >>> accuracy('Cute Dog!', 'Cute Dog.')
    50.0
    >>> accuracy('A Cute Dog!', 'Cute Dog.')
    0.0
    >>> accuracy('cute Dog.', 'Cute Dog.')
    50.0
    >>> accuracy('Cute Dog. I say!', 'Cute Dog.')
    50.0
    >>> accuracy('Cute', 'Cute Dog.')
    100.0
    >>> accuracy('', 'Cute Dog.')
    0.0
    """
    typed_words = split(typed)
    reference_words = split(reference)
    # BEGIN PROBLEM 3
    if len(typed_words) == 0:
        return 0.0
    else:
        i = 0
        same_words = 0
        while i < len(typed_words) and i < len(reference_words):
            if typed_words[i] == reference_words[i]:
                same_words += 1
            i += 1
        words_accuracy = same_words / len(typed_words) * 100
        return words_accuracy
    # END PROBLEM 3


def wpm(typed, elapsed):
    """Return the words-per-minute (WPM) of the TYPED string."""
    assert elapsed > 0, 'Elapsed time must be positive'
    # BEGIN PROBLEM 4
    characters = len(typed)
    words = characters / 5
    minutes = elapsed / 60
    words_per_minute = words / minutes
    return words_per_minute
    # END PROBLEM 4


def autocorrect(user_word, valid_words, diff_function, limit):
    """Returns the element of VALID_WORDS that has the smallest difference
    from USER_WORD. Instead returns USER_WORD if that difference is greater
    than LIMIT.
    """
    # BEGIN PROBLEM 5
    if user_word in valid_words:
        return user_word
    else:
        d = []
        for valid_word in valid_words:
            d.append((valid_word, diff_function(user_word, valid_word, limit)))
        if min(d, key=lambda x: x[1])[1] > limit:
            return user_word
        else:
            return min(d, key=lambda x: x[1])[0]
    # END PROBLEM 5


def swap_diff(start, goal, limit):
    """A diff function for autocorrect that determines how many letters
    in START need to be substituted to create GOAL, then adds the difference in
    their lengths.
    """
    # BEGIN PROBLEM 6
    if len(start) == 1 and len(goal) == 1:
        if start[0] == goal[0]:
            total = 0
        else:
            total = 1
    elif len(start) == len(goal):
        if start[0] == goal[0]:
            total = swap_diff(start[1:], goal[1:], limit)
        else:
            total = swap_diff(start[1:], goal[1:], limit) + 1
    else:
        length = min(len(start), len(goal))
        new_start = start[:length]
        new_goal = goal[:length]
        total = swap_diff(new_start, new_goal, limit) + abs(len(start) - len(goal))
    if total <= limit:
        return total
    else:
        return limit + 1
    # END PROBLEM 6

def edit_diff(start, goal, limit):
    """A diff function that computes the edit distance from START to GOAL."""
    if start == goal: # Fill in the condition
        # BEGIN
        return 0
        # END

    elif len(start) == 0 or len(goal) == 0: # Feel free to remove or add additional cases
        # BEGIN
        edit = max(len(start), len(goal))
        # END

    else:
        add_diff = edit_diff(start[:-1], goal, limit)
        remove_diff = edit_diff(start, goal[:-1], limit)
        substitute_diff = edit_diff(start[:-1], goal[:-1], limit)
        if start[-1] == goal[-1]:
            edit = edit_diff(start[:-1], goal[:-1], limit)
        else:
            edit = min(add_diff, remove_diff, substitute_diff) + 1
        # END
    if edit <= limit:
        return edit
    else:
        return limit + 1


def final_diff(start, goal, limit):
    """A diff function. If you implement this function, it will be used."""
    assert False, 'Remove this line to use your final_diff function'




###########
# Phase 3 #
###########


def report_progress(typed, prompt, id, send):
    """Send a report of your id and progress so far to the multiplayer server."""
    # BEGIN PROBLEM 8
    i = 0
    correct = 0
    while i < min(len(typed), len(prompt)):
        if typed[i] == prompt[i]:
            correct += 1
        else:
            break
        i += 1
    progress = correct / len(prompt)
    send(id, progress)
    return progress
    # END PROBLEM 8


def fastest_words_report(word_times):
    """Return a text description of the fastest words typed by each player."""
    fastest = fastest_words(word_times)
    report = ''
    for i in range(len(fastest)):
        words = ','.join(fastest[i])
        report += 'Player {} typed these fastest: {}\n'.format(i + 1, words)
    return report


def fastest_words(word_times, margin=1e-5):
    """A list of which words each player typed fastest."""
    n_players = len(word_times)
    n_words = len(word_times[0]) - 1
    assert all(len(times) == n_words + 1 for times in word_times)
    assert margin > 0
    # BEGIN PROBLEM 9
    fastest = []
    for j in range(n_players):
        fastest[j] = []
    for i in range(n_words):
        difference = []
        for j in range(n_players):
            difference[j] = elapsed_time(word_times[j][i + 1]) - elapsed_time(word_times[j][i])
        for j in range(n_players):
            if difference[j] - min(difference) <= margin:
                fastest[j].append(word(word_times[j][i + 1]))
    return fastest
    # END PROBLEM 9


def word_time(word, elapsed_time):
    """A data abstrction for the elapsed time that a player finished a word."""
    return [word, elapsed_time]


def word(word_time):
    """An accessor function for the word of a word_time."""
    return word_time[0]


def elapsed_time(word_time):
    """An accessor function for the elapsed time of a word_time."""
    return word_time[1]


enable_multiplayer = True  # Change to True when you


##########################
# Command Line Interface #
##########################


def run_typing_test(topics):
    """Measure typing speed and accuracy on the command line."""
    paragraphs = lines_from_file('data/sample_paragraphs.txt')
    select = lambda p: True
    if topics:
        select = about(topics)
    i = 0
    while True:
        reference = choose(paragraphs, select, i)
        if not reference:
            print('No more paragraphs about', topics, 'are available.')
            return
        print('Type the following paragraph and then press enter/return.')
        print('If you only type part of it, you will be scored only on that part.\n')
        print(reference)
        print()

        start = datetime.now()
        typed = input()
        if not typed:
            print('Goodbye.')
            return
        print()

        elapsed = (datetime.now() - start).total_seconds()
        print("Nice work!")
        print('Words per minute:', wpm(typed, elapsed))
        print('Accuracy:        ', accuracy(typed, reference))

        print('\nPress enter/return for the next paragraph or type q to quit.')
        if input().strip() == 'q':
            return
        i += 1


@main
def run(*args):
    """Read in the command-line argument and calls corresponding functions."""
    import argparse
    parser = argparse.ArgumentParser(description="Typing Test")
    parser.add_argument('topic', help="Topic word", nargs='*')
    parser.add_argument('-t', help="Run typing test", action='store_true')

    args = parser.parse_args()
    if args.t:
        run_typing_test(args.topic)