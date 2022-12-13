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

const char d_messages[][32] = {
    "Push wooden crate",
    "Break rotten crate",
    "Reset tiles"};

const char d_intro_01[][32] = {
    "Okay.. Gravity is out.",
    "Escaping won't be easy,",
    "but I'm sure I can find a way",
    "using those crates.",
    "$"};

const char d_intro_02[][32] = {
    "FEATURE UNLOCKED:",
    "You can now play as Xylia!",
    "Press either trigger to swap",
    "characters and tap the B button",
    "to use their unique ability.",
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
    "1Didn't you say that Jasper wanted  to go out to get a snack?",
    " S02",
    "0Oh, you two go ahead and have fun, I have to catch up on my daily report.",
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

const char d_journal02[][81] = {
    " S12",
    "0Xylia!! Are you okay??",
    "1Luna. Guess what I figured out.",
    " S13",
    "0What is it?",
    " S14",
    "1That Jasper guy?                   He doesn't work for AAA Security.",
    "1He's a fraud, and I think he's     behind the gravity outage.",
    "1I hate zero gravity. HAAAATEEE it.",
    "1He claims that he's off to fix the gravity with that robot of his.",
    "1But he's already lied to us once.  Luna, tell me I'm not crazy.",
    " S15",
    "0No, no you're not crazy.",
    " S16",
    "1(Dangit, they woulda been so cute)",
    " $"};

const char d_journal03[][81] = {
    " S17",
    "1Step away from the controls,       Jasper!",
    " S18",
    "2Uh.. KAM and I almost got the      gravity back.",
    " S17",
    "0Jasper, stand down, or I'll be     forced to use my stun ray.",
    " S18",
    "2Wait.. Do you think this is MY     fault?",
    " S19",
    " M_KILL",
    " ...",
    "0Xylia!?",
    " S21",
    "1Oh, please. You weren't going to   fire that stun gun.",
    " S20",
    "0...I might have!",
    " S22",
    "3Good going, numbskulls. You've     damaged the computer even more.",
    " S23",
    " M_ANATA",
    "0So, if you're not with us.. who AREyou two?",
    " S22",
    "3Stowaways, but we're not malicious.Why would WE turn off the gravity?",
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
    "0KAM, do you think you can try to   get the gravity back on?",
    " S22",
    "3Electronics don't tend to work     after you shoot them.",
    "3Why don't you two look for some    replacement parts?",
    " S23",
    "0Sure thing. We'll.. uh.. be back.",
    " $"};

const char d_journal04[][81] = {
    " S28",
    "3You're too late, humans! Tonight,  we feast on Vegginians!",
    " S17",
    "0Vegons! I should have known!",
    " S27",
    "1Is that the species with the reallybad poetry?",
    " S29",
    "2No, those are humans.",
    " S27",
    "1Look, do you want us to save you ornot?",
    " S17",
    "0Don't be afraid, Vegginian! Help ison the way!",
    " $"
};

const char d_journal05[][81] = {
    " S30",
    "0...",
    "0Mr. Tomato! Are you okay?",
    " S31",
    "2Absolutely steamed! Clearly, one   security guard was not enough.",
    "2We needed at least three.",
    " S32",
    "0What are we going to do?",
    " S31",
    "2Young lady, you are the security   guard.",
    "2You're the only one qualified to   handle this situation.",
    " S32",
    "0Oh... right. Well, we're trying to get the gravity back on.",
    " S31",
    "2Well, hurry up, then!",
    " $"
};

const char d_journal06[][81] = {
    " S33",
    "0Finally! There it is! Time to get  it back to Jasper.",
    " S34",
    "2Looks like the installation was a  success! Gravity is back... here.",
    "2Now we just need to get to the     other control panel.",
    "2Half the ship is still out of      gravity.",
    "2(Despite your best efforts.)",
    " S35",
    "1Hey! How was I supposed to know    Vegons were on board?",
    " S36",
    "0We'll escort you. We should get    everything back in no time!",
    " S35",
    "1Ugh, do we have to bring Jasper?",
    " $"
};

const char d_intro_03[][32] = {
    "FEATURE UNLOCKED:",
    "You can now play as Jasper!",
    "Press either trigger to swap",
    "characters and tap the B button",
    "to use their unique ability.",
    "$"};

/*
const char d_journal07[][81] = {
    "2Am I crazy for thinking this is kind of fun?",
    "0I'll admit, I didn't expect this trip to be so exciting.",
    "1Tell me, are you stowing away for the adventure or because you're poor?",
    "2Both.",
    "1You know..",
    "0Be nice, Xylia.",
    "1That sounds nice. No image to keep up, no one telling you what to do.",
    "2The freedom is nice. Being hungry all the time is not."
    "2I grew up in the space circus, you know.",
    "0No way! I wonder if Xylia and I saw you at some point. What did you do?",
    "2I ran the lightboard and did repairs.",
    "1Last time I went to the circus, the flashing lights made me queasy. So I guess we're even.",
    "2Nah. It'd have to happen twice for us to be even.",
    " $"
}

const char d_journal08[][81] = {
    "0So how many of you ARE there?",
    "3Enough to defeat you three!",
    "1Stand down, Vegon!",
    "0Jasper!",
    "2What? I figured she wasn't going to use it.",
    "0I really was that time!"
    " $"
}

const char d_journal09[][81] = {
    "0It's over, Vegons! Surrender now, or else!",
    "3Or else what?",
    "1C'mon, Luna.",
    "2You got this!",
    "3Bad move."
}

const char d_journal10[][81] = {
    "1Luna? Are you okay?",
    "0...Ow.",
    "2Yeah, that stun beam hurts, huh.",
    "0..I really sorry, guys. I.. I failed you. I'm not good enough to be a security guard.",
    "2Oh come on, you've done a great job so far! You just don't like zapping people. But that can be fixed.",
    "0What do you mean?",
    "2See that stunned Vegon on the ground? He's not bothering nobody. No one says you can't zap him as he is.",
    "0That seems cruel.",
    "2Dude, he was literally right about to eat your clients.",
    "0...Okay... You can do this, Luna.",
    "2Uh.. Luna, that's enough.",
    "1Jasper! You broke sweet, innocent Luna!"
    "0It's all done, isn't it? The Vegons are in jail, the Vegginians are happy, and I'm getting paid.",
    "2This is where I hitch a ride on the next spaceship. I'll admit though, I'm gonna miss you guys.",
    "1Hey.. When can I see you again?",
    "0This is stupid. Why don't we three sail off together? We're all adults here, we can do what we want.",
    "1What about your job?",
    "0What about your lack of one?",
    "1...Touché.",
    "2I guess it's settled, then. Off to the next adventure?",
    "0Yeah!",
    " $"
}
*/

const char d_credits[][32] = {
    "CORNUCOPIA",
    "Character design: Madelyn Watts",
    "Kickstarter backers",
    " $"
};

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
    default:
    {
        return &d_messages[position];
        break;
    }
    }
}