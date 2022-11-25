const char d_messages[][32] = {
    "Push wooden crate"};

const char d_intro_01[][32] = {
    "Testing? Testing? This is KAM,",
    "Coming to you loud and clear",
    "over the intercom... I hope.",
    "So it looks like the artificial",
    "gravity, much like what you're",
    "clinging to, is AWOL.",
    "But it's no matter - all the",
    "furniture is bolted down.",
    "Except for the crates, that is.",
    "I'm sure they'll come in handy.",
    "$"};

void const *resolve_dialogue(int requested_dialogue, int position = 0)
{
    switch (requested_dialogue)
    {
    case 1:
    {
        return &d_intro_01[position];
        break;
    }
    default:
    {
        return &d_messages[position];
        break;
    }
    }
}