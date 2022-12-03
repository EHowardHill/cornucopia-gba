/* 

    strcmp license:

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
    <https://www.gnu.org/licenses/>.  */

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

const char d_messages[][32] = {
    "Push wooden crate",
    "Break rotten crate"};

const char d_intro_01[][32] = {
    "Okay.. Gravity is out.",
    "Escaping won't be easy,",
    "but I'm sure I can find a way",
    "using those crates.",
    "$"};

const char d_journal01[][81] = {
    " S01",
    "0Dear diary, first day as a securityguard is finally over!",
    "0AAA Security put me on this cruise-liner called the 'Cornucopia'.",
    "0All the passengers are Vegginians, and they are SO chill!",
    " S02",
    "0It would be boring, but I convincedXylia to come along.",
    "0Her parents bought her a ticket so we're sharing a cabin.",
    "0She, uh.. doesn't like it when her parents buy her stuff,",
    " S03",
    "0but she's been quiet about it.",
    " S02",
    "0We spent most of the day playing   shuffleboard with the Vegginians",
    "0and my coworker, Jasper.           Jasper seems cool.",
    "0Does he think Xylia is cute?       Only time will tell.",
    " S04",
    "0He made this little robot named    KAM, I think. It's pretty smart.",
    "0I have no idea why he's in securityif  he likes making robots so much,",
    "0but it's whatever.                 So excited for tomorrow!",
    " S03",
    "1Hope you're not writing anything inthere you want to keep secret.",
    " S00",
    "0How come?",
    "1You mumbled the whole thing out    loud as you were writing.",
    " S02",
    "0Oh.. hehe.",
    " S00",
    "1Didn't you say that Jasper wanted  to go out to get a snack",
    "1before the coffee shop closed?",
    " S02",
    "0Oh, you go ahead and have fun, I   have to catch up on my daily report.",
    " S05",
    "1Alright, then.",
    "1I can hear you giggling from all   the way over here.",
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
    "0How long has it been? It is time tosee how Jasper and Xylia are doing?",
    " S09",
    "Ehh.. I'm sure they're fine.",
    " S10",
    "...",
    " S11",
    "0What the-                          Who turned the gravity off?",
    "0I guess it's, uh.. It's REALLY     time to check on the others.",
    " $"};

void const *resolve_dialogue(int requested_dialogue, int position = 0)
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
    default:
    {
        return &d_messages[position];
        break;
    }
    }
}