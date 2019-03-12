#!/usr/bin/env python3

from collections import Counter
from datetime import datetime
import sys

import numpy as np 
import pandas as pd 
from absl import flags, app

FLAGS = flags.FLAGS

flags.DEFINE_string('day', None, 'Day of the matchup in format yyyy-mm-dd. If not set, current day will be used')
flags.DEFINE_string('winner', None, 'Name of the winner (player with lower rating value if drawn matchup is adding)')
flags.DEFINE_string('looser', None, 'Name of the looser (player with greater rating value if drawn matchup is adding)')
flags.DEFINE_string('score', None, "Result of match in W:L format (W - winner's won sets, L - looser's won sets)")
flags.DEFINE_string('ball', 'yellow', 'Type of ball used for matchup')
flags.mark_flags_as_required(['winner', 'looser', 'score'])


def date_is_correct(date):
    if not isinstance(date, str):
        return False
    date_items = date.split('-')
    if len(date_items) != 3:
        return False
    for date_item in date_items:
        if not date_item.isdigit():
            return False
    year = int(date_items[0])
    if year < 1000 or year > 2100:
        return False
    month = int(date_items[1])
    if month < 1 or month > 12:
        return False
    day = int(date_items[2])
    months31 = [1, 3, 5, 7, 8, 10, 12]
    months30 = [4, 6, 9, 11]
    if month in months31:
        return day > 0 and day < 32
    elif month in months30:
        return day > 0 and day < 31
    else:
        if year % 4 != 0:
            return day > 0 and day < 29
        elif year % 100 == 0 and year % 400 != 0:
            return day > 0 and day < 29
        else:
            return day > 0 and day < 30


def check_player(player, games):
    known_players = set(games['Winner'].tolist() + games['Looser'].tolist())
    if player not in known_players:
        print('player {} has no mathups at database, Do you want to add him? ([y]/n)'.format(player))
        confirm = sys.stdin.readline().strip()
        if confirm == 'n':
            print('OK')
            return False
        elif confirm != 'y' and confirm != '':
            print('Response is incorrect')
            return False
        print('Added new player')
        return True
    else:
        return True


def ball_is_correct(ball):
    if not isinstance(ball, str):
        return False
    return ball in ['yellow', 'blue', 'red']


def score_is_correct(score):
    if not isinstance(score, str):
        return False
    score_items = score.split(':')
    if len(score_items) != 2:
        return False
    for score_item in score_items:
        if not score_item.isdigit() or int(score_item) < 0:
            return False
    return True


def main(_):
    games_scv_filename = 'games.csv' 
    games = pd.read_csv(games_scv_filename)
    
    game_to_add = {}

    if FLAGS.day is None:    
        cur_date = datetime.now()
        cur_year = str(cur_date.year)
        cur_month = '0' * (cur_date.month < 10) + str(cur_date.month)
        cur_day = '0' * (cur_date.day < 10) + str(cur_date.day)
        cur_day_of_year = '{}-{}-{}'.format(cur_year, cur_month, cur_day)
        game_to_add['Date'] = cur_day_of_year
    else:
        if date_is_correct(FLAGS.day):
            game_to_add['Date'] = FLAGS.day
        else:
            print('Entered date is incorrect or has wrong format')
            print('Matchup adding failed')
            return

    played_days = games['Date'].tolist()
    played_days_counts = Counter()
    played_days_counts.update(played_days)
    if game_to_add['Date'] not in played_days_counts.keys():
        game_to_add['Game of the day'] = 1
    else:
        game_to_add['Game of the day'] = played_days_counts[game_to_add['Date']] + 1

    if check_player(FLAGS.winner, games):
        game_to_add['Winner'] = FLAGS.winner
    else:
        print('Matchup adding failed')
        return 

    if check_player(FLAGS.looser, games):
        game_to_add['Looser'] = FLAGS.looser
    else:
        print('Matchup adding failed')
        return 

    if score_is_correct(FLAGS.score):
        game_to_add['Score'] = FLAGS.score
    else:
        print('Matchup adding failed: score {} is incorrect'.format(FLAGS.score))
        return 

    if ball_is_correct(FLAGS.ball):
        game_to_add['Ball'] = FLAGS.ball
    else:
        print('Matchup adding failed: ball {} is incorrect'.format(FLAGS.ball))
        return 
    
    games = games.append(game_to_add, ignore_index=True)
    games.to_csv(games_scv_filename, index=False)
    print('Matchup adding succeeded')


if __name__=='__main__':
    app.run(main)
