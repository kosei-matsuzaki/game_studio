#include <stdio.h>

//string of card mark(0 ~ 3)
const char* p_mark(int m) {
    switch (m) {
    case 0: return "\x1b[34m♠\x1b[0m";
    case 1: return "\x1b[32m♣\x1b[0m";
    case 2: return "\x1b[31m♥\x1b[0m";
    case 3: return "\x1b[33m♦\x1b[0m";
    default: return "?";
    }
}

//string of card mark(0 ~ 12)
const char* p_number(int m) {
    switch (m) {
    case 0: return "A";
    case 1: return "2";
    case 2: return "3";
    case 3: return "4";
    case 4: return "5";
    case 5: return "6";
    case 6: return "7";
    case 7: return "8";
    case 8: return "9";
    case 9: return "10";
    case 10: return "J";
    case 11: return "Q";
    case 12: return "K";
    default: return "?";
    }
}

//string of player name
const char* p_name(int m) {
    switch (m) {
        case 0: return "\x1b[92mYou\x1b[0m ";
        case 1: return "\x1b[37mCom1\x1b[0m";
        case 2: return "\x1b[37mCom2\x1b[0m";
        case 3: return "\x1b[37mCom3\x1b[0m";
        case 4: return "\x1b[37mCom4\x1b[0m";
        default: return "Who?";
    }
}

//string of player hand
const char* p_hand(int score) {
    switch (score / 10000000) {
    case 9: return "Royal Straight Flush"; break;
    case 8: return "Straight Flush"; break;
    case 7: return "Four of a Kind"; break;
    case 6: return "Full House"; break;
    case 5: return "Flush"; break;
    case 4: return "Straight"; break;
    case 3: return "Three of a Kind"; break;
    case 2: return "Two Pair"; break;
    case 1: return "One Pair"; break;
    case 0: return "High Card"; break;
    default: return "Unknown Hand"; break;
    }
}

//string of round
const char* p_round_name(int situation) {
    switch (situation) {
    case 0: return "PRE-FLOP"; break;
    case 3: return "FLOP"; break;
    case 4: return "TURN"; break;
    case 5: return "RIVER"; break;
    default: return "UNKNOWN"; break;
    }
}