/*
license for Strcmp:

Copyright (C) 1991-2022 Free Software Foundation, Inc.
This file is part of the GNU C Library.
The GNU C Library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
The GNU C Library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
You should have received a copy of the GNU Lesser General Public
License along with the GNU C Library; if not, see
<https://www.gnu.org/licenses/>.
*/

int strcmp(const char *p1, const char *p2)
{
    const unsigned char *s1 = (const unsigned char *)p1;
    const unsigned char *s2 = (const unsigned char *)p2;
    unsigned char c1, c2;
    do
    {
        c1 = (unsigned char)*s1++;
        c2 = (unsigned char)*s2++;
        if (c1 == '\0')
            return c1 - c2;
    } while (c1 == c2);
    return c1 - c2;
}

const char d_messages[][28] = {
    "Push wooden crate",
    "Break rotten crate",
    "Reset tiles"};

const char d_intro_01[][28] = {
    "Okay.. Gravity is out.",
    "Escaping won't be easy,",
    "but I'm sure I can find a",
    "way using those crates.",
    "$"};

const char d_intro_02[][28] = {
    "FEATURE UNLOCKED:",
    "You can play as Xylia!",
    "Press the triggers to swap",
    "Tap the B button to use",
    "their unique abilities.",
    "$"};

const char d_journal01[][57] = {
    " S01",
    "0Dear diary, first day as a  security guard is over!",
    "0AAA Security put me on this ship called the Cornucopia.",
    "0It's a Vegginian ship, and  they are SO chill!",
    " S02",
    "0It would be boring, but I   got Xylia to come along.",
    "0Her parents bought her a    ticket, and uh..",
    "0She doesn't like it when herparents buy her stuff,",
    " S03",
    "0but she's been really quiet about it.",
    " S02",
    "0We spent most of the day    playing shuffleboard with",
    "0the Vegginians and my       coworker, Jasper.",
    "0Jasper kept trying to be    smooth with Xylia.",
    "0Does he think she's cute?   Only time will tell.",
    " S04",
    "0He made this smart little   robot named KAM.",
    "0I have no idea why he's in  security if he likes making",
    "0robots so much. Anyway, I'm so excited for tomorrow!",
    " S03",
    "1Hope there's nothing secret in there.",
    " S00",
    "0How come?",
    "1You mumbled the whole thing aloud, you know.",
    " S02",
    "0Oh.. hehe.",
    " S00",
    "1Didn't you say Jasper wantedto go out to get a snack?",
    " S02",
    "0You two go ahead, I have to write my daily report.",
    " S05",
    "1Alright, then.",
    "1I can hear you giggling fromway over here.",
    " S06",
    "0I'm not, I'm not.",
    "1Luna, I don't believe you.",
    " S07",
    "0...",
    "0....",
    "0...Alright, now we wait.",
    " S08",
    " M_KILL",
    "...uggggggh",
    "0Welp, seems like high time  to check on the lovebirds.",
    " S09",
    "..Eh, I'm sure they're fine.",
    " S10",
    "...",
    " S11",
    "0What the-                   Who turned the gravity off?",
    "0I guess it's REALLY time to check on the others.",
    " $"};

const char d_journal02[][57] = {
    " S12",
    "0Xylia!! Are you okay??",
    "1Luna. Guess what.",
    " S13",
    "0What is it?",
    " S14",
    "1That Jasper guy? He doesn't work for AAA Security.",
    "1Luna, I think he's behind   the gravity outage.",
    "1That dirty rat... Ugh,      I HATE this.",
    "1He claims he's going to fix the gravity with his robot.",
    "1He's already lied. Luna,    tell me I'm not crazy.",
    " S15",
    "0No, no you're not crazy.",
    " S16",
    "1(Dangit, they woulda been socute together)",
    " $"};

const char d_journal03[][57] = {
    " S17",
    "1Step away from the controls,Jasper!",
    " S18",
    "2Uh.. KAM and I almost got   the gravity back.",
    " S17",
    "0Jasper, stand down, or I'll use my stun ray.",
    " S18",
    "2Wait.. Do you think this is MY fault?",
    " S19",
    " M_KILL",
    " ...",
    "0Xylia!?",
    " S21",
    "1Oh, please. You weren't     going to use this.",
    " S20",
    "0...I might have!",
    " S22",
    "3Good going, numbskulls. Now it's even MORE broken.",
    " S23",
    " M_ANATA",
    "0So, if you're not with us.. who ARE you two?",
    " S22",
    "3Stowaways, but we're not    malicious.",
    "3What would WE get from      turning off the gravity?",
    " S24",
    "1I don't know - you tell me.",
    " S25",
    "2...Ow, my head...",
    " S26",
    " M_KILL",
    "0Xylia! Cut that out!",
    " S21",
    "1Sorry, I couldn't help it.",
    " S23",
    "0KAM, what do we need to do?",
    " S22",
    "3Electronics don't tend to   work after you shoot them.",
    "3Why don't you two look for  some replacement parts?",
    " S23",
    "0Sure thing. We'll.. uh..    We'll be back.",
    " $"};

const char d_journal04[][57] = {
    " S28",
    "3You're too late, humans!",
    "3Tonight,                    we feast on Vegginians!",
    " S17",
    "0Vegons! I should have known!",
    " S27",
    "1Is that the species with thereally bad poetry?",
    " S29",
    "2No, those are humans.",
    " S27",
    "1Look, do you want us to saveyou or not?",
    " S17",
    "0Don't be afraid, Vegginian! Help is on the way!",
    " $"};

const char d_journal05[][57] = {
    " S30",
    "0...",
    "0Mr. Tomato! Are you okay?",
    " S31",
    "2Absolutely steamed! One     guard was not enough.",
    "2We needed at least three.",
    " S32",
    "0What are we going to do?",
    " S31",
    "2Young lady, you are the     security guard.",
    "2You are the only one who canhandle this situation.",
    " S32",
    "0Oh..  Well, we're trying to get the gravity back on.",
    " S31",
    "2Hurry up, then!",
    " $"};

const char d_journal06[][57] = {
    " S33",
    "0Finally! There it is! Time  to get back to Jasper.",
    " S34",
    "2Looks like the installation was a success!",
    "2Now we just need to get to  the other control panel.",
    "2Half the ship is still out  of gravity.",
    "2(Despite your best efforts.)",
    " S35",
    "1Hey! How was I supposed to  know it was Vegons?",
    " S36",
    "0We'll escort you. Everythingwill be back in no time!",
    " S35",
    "1Ugh, do we have to bring    Jasper?",
    " $"};

const char d_intro_03[][28] = {
    "FEATURE UNLOCKED:",
    "You can play as Jasper!",
    "Press the triggers to swap",
    "Tap the B button to use",
    "their unique abilities.",
    "$"};

const char d_intro_04[][28] = {
    "WARNING: SATELLITE DETECTED",
    "Jasper's third eye is very",
    "sensitive, and it may get",
    "damaged if you use it in",
    "range of the satellite!",
    "$"};

const char d_boss02[][28] = {
    "Ugh! Out of gravity range,",
    "And now another Vegon?",
    "This better go quick.",
    "$"};

const char d_journal07[][57] = {
    " S42",
    "0So how many of you even     ARE there?",
    " S28",
    "3Enough to defeat you three!",
    " S42",
    "1Stand down, Vegon!",
    " S43",
    "0Jasper!",
    "0I was right about to shoot! Promise!",
    " S44",
    "2Hey, I'm sure there's more.",
    " $"};

const char d_journal08[][57] = {
    " S38",
    "2Am I crazy for thinking thisis kind of fun?",
    " S39",
    "1I'll admit, I didn't expect this trip to be exciting.",
    " S41",
    "1Tell me, are you stowing    away for the adventure,",
    "1Or are you just poor?",
    " S40",
    "0Xylia! Be nice!",
    " S38b",
    "2Both.",
    " S39",
    "1That sounds nice. No image  to keep up.",
    "1No one telling you what you can and can't do.",
    " S38b",
    "2The freedom is nice. Being  hungry all the time is not.",
    "2I grew up in the space      circus, you know.",
    " S39",
    "1Huh.. I wonder if Luna and Iever saw you.",
    "1What did you do?",
    " S38b",
    "2I ran the electronics and   did repairs.",
    " S39",
    "1Last time I went to the     circus, you know,",
    "1The flashing lights made me queasy.",
    "1So I guess we're even.",
    " S38b",
    "2Nah. It'd have to happen    twice for us to be even.",
    " S39",
    "1Grrr...",
    " $"};

const char d_journal09[][57] = {
    " S42",
    "0It's over, Vegons!          Surrender now, or else!",
    " S28",
    "3Or else what?",
    " S46",
    "1C'mon, Luna.",
    " S47",
    "2Shoot him already!",
    " S48",
    "0I'm aiming! Gimme a moment!",
    " S57",
    "3Bad move, security guard!",
    " $"};

const char d_journal10[][57] = {
    " S49",
    "1Luna? Are you okay?",
    "0...Ow.",
    "2(Yeah, that stun beam hurts, huh.)",
    " S50",
    "0..I really sorry, guys.",
    "0I.. I failed you. I'm not   good enough to be",
    "0a security guard.",
    " S51",
    "2Oh come on, you could have  got that Vegon first time,",
    "2You just hesitated a little too long.",
    "1Luna, it was really hard    without you.",
    " S58",
    "0...",
    "1I can't breathe, Luna.",
    "0(...Thank you guys.)",
    "1No problem, but I eventuallyneed to breathe.",
    " S52",
    "0SEVERAL DAYS LATER",
    "0Well... that's that.",
    " S53",
    "0It's all done, isn't it? TheVegons are off to jail,",
    "0the Vegginians are happy,   and I'm getting paid.",
    " S55",
    "2This is where I hitch a rideon the next spaceship.",
    "2I'll admit though, I'm gonnamiss you guys.",
    " S54",
    "1Hey.. When can I see you    again?",
    " S56",
    "0This is stupid. Why don't wethree sail off together?",
    "0We're all adults here, we   can do what we want.",
    " S54",
    "1What about your job?",
    " S56",
    "0What about your lack of one?",
    " S54",
    "1...Touché.",
    " S55",
    "2I guess it's settled, then. Off to the next adventure?",
    " S56",
    "0Yeah!",
    " $"};

void const *
resolve_dialogue(int requested_dialogue, int position = 0)
{
    switch (requested_dialogue)
    {
    case 1:
    {
        return &d_intro_01[position];
        break;
    }
    case 2:
    {
        return &d_journal01[position];
        break;
    }
    case 3:
    {
        return &d_journal02[position];
        break;
    }
    case 4:
    {
        return &d_intro_02[position];
        break;
    }
    case 5:
    {
        return &d_journal03[position];
        break;
    }
    case 6:
    {
        return &d_journal04[position];
        break;
    }
    case 7:
    {
        return &d_journal05[position];
        break;
    }
    case 8:
    {
        return &d_journal06[position];
        break;
    }
    case 9:
    {
        return &d_intro_03[position];
        break;
    }
    case 10:
    {
        return &d_intro_04[position];
        break;
    }
    case 11:
    {
        return &d_boss02[position];
        break;
    }

    // final bit
    case 12:
    {
        return &d_journal07[position];
        break;
    }
    case 13:
    {
        return &d_journal08[position];
        break;
    }
    case 14:
    {
        return &d_journal09[position];
        break;
    }
    case 15:
    {
        return &d_journal10[position];
        break;
    }
    default:
    {
        return &d_messages[position];
        break;
    }
    }
}