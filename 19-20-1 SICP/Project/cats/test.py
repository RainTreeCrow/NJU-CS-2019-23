from utils import *
from ucb import main, interact, trace
from datetime import datetime

import string

def lines_from_file(path):
    with open(path, 'r') as f:
        return [line.strip() for line in f.readlines()]

punctuation_remover = str.maketrans('', '', string.punctuation)

def remove_punctuation(s):
    return s.strip().translate(punctuation_remover)

def lower(s):
    return s.lower()

def split(s):
    return s.split()

def choose(paragraphs, select, k):
    i = 0
    chosen_paragraph = ''
    for paragraph in paragraphs:
        if select(paragraph):
            if i == k:
                chosen_paragraph = paragraph
                break
            i += 1
    return chosen_paragraph

def about(topic):
    assert all([lower(x) == x for x in topic])
    def select(paragraph):
        words = split(lower(remove_punctuation(paragraph)))
        words_in = 0
        for a_word in words:
            if a_word in topic:
                words_in += 1
        return words_in != 0
    return select

def accuracy(typed, reference):
    typed_words = split(typed)
    reference_words = split(reference)
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

def wpm(typed, elapsed):
    assert elapsed > 0
    characters = len(typed)
    words = characters / 5
    minutes = elapsed / 60
    words_per_minute = words / minutes
    return words_per_minute

def autocorrect(user_word, valid_words, diff_function, limit):
    if user_word in valid_words:
        return user_word
    else:
        min = limit + 1
        correction = user_word
        for valid_word in valid_words:
            if diff_function(user_word, valid_word, limit) <= limit:
                if diff_function(user_word, valid_word, limit) < min:
                    correction = valid_word
                    min = diff_function(user_word, valid_word, limit)
        return correction

def swap_diff(start, goal, limit):
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

def edit_diff(start, goal, limit):
    if start == goal:
        edit = 0
    elif len(start) == 0 or len(goal) == 0:
        edit = max(len(start), len(goal))
    else:
        add_diff = edit_diff(start[:-1], goal, limit)
        remove_diff = edit_diff(start, goal[:-1], limit)
        substitute_diff = edit_diff(start[:-1], goal[:-1], limit)
        if start[-1] == goal[-1]:
            edit = edit_diff(start[:-1], goal[:-1], limit)
        else:
            edit = min(add_diff, remove_diff, substitute_diff) + 1
    if edit <= limit:
        return edit
    else:
        return limit + 1

def report_progress(typed, prompt):
    i = 0
    correct = 0
    while i < min(len(typed), len(prompt)):
        if typed[i] == prompt[i]:
            correct += 1
        else:
            break
        i += 1
    progress = correct / len(prompt)
    return progress

def fastest_words_report(word_times):
    fastest = fastest_words(word_times)
    report = ''
    for i in range(len(fastest)):
        words = ','.join(fastest[i])
        report += 'Player {} typed these fastest: {}\n'.format(i + 1, words)
    return report

def fastest_words(word_times, margin=1e-5):
    n_players = len(word_times)
    n_words = len(word_times[0]) - 1
    assert all(len(times) == n_words + 1 for times in word_times)
    assert margin > 0
    fastest = []
    for j in range(n_players):
        fastest.append([])
    for i in range(n_words):
        difference = []
        for j in range(n_players):
            difference.append(elapsed_time(word_times[j][i + 1]) - elapsed_time(word_times[j][i]))
        for j in range(n_players):
            if difference[j] - min(difference) <= margin:
                fastest[j].append(word(word_times[j][i + 1]))
    return fastest

def word_time(word, elapsed_time):
    return [word, elapsed_time]

def word(word_time):
    return word_time[0]

def elapsed_time(word_time):
    return word_time[1]

[[word_time('START', 1), word_time('perth' , 1.2), word_time('chrematistic' , 2.2),
  word_time('proctotomy' , 2.4000000000000004), word_time('bicetyl' , 2.6000000000000005)],
 [word_time('START', 1), word_time('perth' , 1.2), word_time('chrematistic' , 1.5333333333333332),
  word_time('proctotomy' , 2.533333333333333), word_time('bicetyl' , 2.8666666666666667)],
 [word_time('START', 1), word_time('perth' , 2.0), word_time('chrematistic' , 2.25),
  word_time('proctotomy' , 2.75), word_time('bicetyl' , 3.0)]]
0.16666666666666666

[['perth', 'proctotomy', 'bicetyl'], ['perth', 'chrematistic', 'bicetyl'], ['chrematistic', 'bicetyl']]

print(fastest_words([[word_time('START', 1), word_time('perth' , 1.2), word_time('chrematistic' , 2.2),
  word_time('proctotomy' , 2.4000000000000004), word_time('bicetyl' , 2.6000000000000005)],
 [word_time('START', 1), word_time('perth' , 1.2), word_time('chrematistic' , 1.5333333333333332),
  word_time('proctotomy' , 2.533333333333333), word_time('bicetyl' , 2.8666666666666667)],
 [word_time('START', 1), word_time('perth' , 2.0), word_time('chrematistic' , 2.25),
  word_time('proctotomy' , 2.75), word_time('bicetyl' , 3.0)]],
0.16666666666666666))