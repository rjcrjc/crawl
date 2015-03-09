enum species_flag
{
    SPF_NONE        = 0,
    SPF_ELVEN       = 1 << 0, /// If this species counts as an elf
    SPF_DRACONIAN   = 1 << 1, /// If this is a draconian subspecies
    SPF_ORCISH      = 1 << 2, /// If this species is a kind of orc
    SPF_NO_HAIR     = 1 << 3, /// If members of the species are hairless
    SPF_SMALL_TORSO = 1 << 4, /// Torso is smaller than body
};
DEF_BITFIELD(species_flags, species_flag);

struct level_up_mutation
{
    mutation_type mut; ///< What mutation to give
    int mut_level; ///< How much to give
    int xp_level; ///< When to give it (if 1, is a starting mutation)
};

struct species_def
{
    const char* abbrev; ///< Two-letter abbreviation
    const char* name; ///< Main name
    const char* adj_name; ///< Adjectival form of name; if null, use name
    const char* genus_name; ///< Genus name; if null, use name
    species_flags flags; ///< Miscellaneous flags
    int xp_mod; ///< Experience level modifier
    int hp_mod; ///< HP modifier (in tenths)
    int mp_mod; ///< MP modifier (in tenths)
    int stealth_mod; ///< Stealth modifier
    int mr_mod; ///< MR modifier (multiplied by XL for base MR)
    monster_type monster_species; ///< Corresponding monster (for display)
    habitat_type habitat; ///< Where it can live; HT_WATER -> no penalties
    undead_state_type undeadness; ///< What kind of undead (if any)
    size_type size; ///< Size of body
    int s, i, d; ///< Starting stats contribution
    bool gain_s, gain_i, gain_d; ///< Which stats to gain on level-up
    int how_often; ///< When to level-up stats
    vector<level_up_mutation> level_up_mutations; ///< Mutations on level-up
    vector<string> verbose_fake_mutations; ///< Additional information on 'A'
    vector<string> terse_fake_mutations; ///< Additional information on '%'
    vector<job_type> recommended_jobs; ///< Which jobs are "good" for it
};

static const map<species_type, species_def> species_data =
{

{ SP_CENTAUR, {
    "Ce",
    "Centaur", nullptr, nullptr,
    SPF_SMALL_TORSO,
    -1, 1, -1,
    9, 3,
    MONS_CENTAUR,
    HT_LAND, US_ALIVE, SIZE_LARGE,
    10, 7, 4, // 21
    true, false, true, 4,
    { { MUT_TOUGH_SKIN, 3, 1 }, { MUT_FAST, 2, 1 },  { MUT_DEFORMED, 1, 1 },
      { MUT_HOOVES, 3, 1 }, },
    {},
    {},
    { JOB_FIGHTER, JOB_GLADIATOR, JOB_HUNTER, JOB_WARPER, JOB_ARCANE_MARKSMAN },
} },

{ SP_DEEP_DWARF, {
    "DD",
    "Deep Dwarf", "Dwarven", "Dwarf",
    SPF_NONE,
    -1, 2, 0,
    15, 6,
    MONS_DEEP_DWARF,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    11, 8, 8, // 27
    true, true, false, 4,
    { { MUT_SLOW_HEALING, 3, 1 }, { MUT_PASSIVE_MAPPING, 1, 1 },
      { MUT_PASSIVE_MAPPING, 1, 9 }, { MUT_PASSIVE_MAPPING, 1, 18 },
      { MUT_NEGATIVE_ENERGY_RESISTANCE, 1, 14 }, },
    { "You are resistant to damage.",
      "You can recharge devices by infusing magical energy." },
    { "damage resistance", "recharge devices" },
    { JOB_FIGHTER, JOB_HUNTER, JOB_BERSERKER, JOB_NECROMANCER,
      JOB_EARTH_ELEMENTALIST },
} },

{ SP_DEEP_ELF, {
    "DE",
    "Deep Elf", "Elven", "Elf",
    SPF_ELVEN,
    -1, -2, 3,
    15, 4,
    MONS_ELF,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    5, 12, 10, // 27
    false, true, false, 4,
    {},
    {},
    {},
    { JOB_WIZARD, JOB_CONJURER, JOB_SUMMONER, JOB_NECROMANCER,
      JOB_FIRE_ELEMENTALIST, JOB_ICE_ELEMENTALIST, JOB_AIR_ELEMENTALIST,
      JOB_EARTH_ELEMENTALIST, JOB_VENOM_MAGE },
} },

{ SP_DEMIGOD, {
    "Dg",
    "Demigod", "Divine", nullptr,
    SPF_NONE,
    -2, 1, 2,
    15, 4,
    MONS_DEMIGOD,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    11, 12, 11, // 34
    false, false, false, 28, // No natural stat gain (double chosen instead)
    { { MUT_SUSTAIN_ABILITIES, 1, 1 }, },
    {},
    {},
    { JOB_TRANSMUTER, JOB_CONJURER, JOB_FIRE_ELEMENTALIST, JOB_ICE_ELEMENTALIST,
      JOB_AIR_ELEMENTALIST, JOB_EARTH_ELEMENTALIST },
} },

// Keep this above the other draconians, so get_species_by_abbrev works
{ SP_BASE_DRACONIAN, {
    "Dr",
    "Draconian", nullptr, nullptr,
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, },
    {},
    {},
    { JOB_BERSERKER, JOB_TRANSMUTER, JOB_CONJURER, JOB_FIRE_ELEMENTALIST,
      JOB_ICE_ELEMENTALIST, JOB_AIR_ELEMENTALIST, JOB_EARTH_ELEMENTALIST,
      JOB_VENOM_MAGE },
} },

{ SP_RED_DRACONIAN, {
    "Dr",
    "Red Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_RED_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, { MUT_HEAT_RESISTANCE, 1, 7 }, },
    { "You can breathe blasts of fire." },
    { "breathe fire" },
    {}, // not a starting race
} },

{ SP_WHITE_DRACONIAN, {
    "Dr",
    "White Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_WHITE_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, { MUT_COLD_RESISTANCE, 1, 7 }, },
    { "You can breathe waves of freezing cold.",
      "You can buffet flying creatures when you breathe cold." },
    { "breathe frost" },
    {}, // not a starting race
} },

{ SP_GREEN_DRACONIAN, {
    "Dr",
    "Green Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_GREEN_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, { MUT_POISON_RESISTANCE, 1, 7 },
      { MUT_STINGER, 1, 14 }, },
    { "You can breathe blasts of noxious fumes." },
    { "breathe noxious fumes" },
    {}, // not a starting race
} },

{ SP_YELLOW_DRACONIAN, {
    "Dr",
    "Yellow Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_YELLOW_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, { MUT_ACIDIC_BITE, 1, 14 }, },
    { "You can spit globs of acid.", "You are resistant to acid." },
    { "spit acid", "acid resistance" },
    {}, // not a starting race
} },

{ SP_GREY_DRACONIAN, {
    "Dr",
    "Grey Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_GREY_DRACONIAN,
    HT_AMPHIBIOUS, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, { MUT_UNBREATHING, 1, 7 }, },
    { "You can walk through water." },
    { "walk through water" },
    {}, // not a starting race
} },

{ SP_BLACK_DRACONIAN, {
    "Dr",
    "Black Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_BLACK_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, { MUT_SHOCK_RESISTANCE, 1, 7 },
      { MUT_BIG_WINGS, 1, 14 }, },
    { "You can breathe wild blasts of lightning." },
    { "breathe lightning" },
    {}, // not a starting race
} },

{ SP_PURPLE_DRACONIAN, {
    "Dr",
    "Purple Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 6,
    MONS_PURPLE_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, },
    { "You can breathe bolts of dispelling energy." },
    { "breathe power" },
    {}, // not a starting race
} },

{ SP_MOTTLED_DRACONIAN, {
    "Dr",
    "Mottled Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_MOTTLED_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, },
    { "You can spit globs of burning liquid.",
      "You can ignite nearby creatures when you spit burning liquid." },
    { "breathe sticky flame splash" },
    {}, // not a starting race
} },

{ SP_PALE_DRACONIAN, {
    "Dr",
    "Pale Draconian", "Draconian", "Draconian",
    SPF_DRACONIAN,
    -1, 1, 0,
    12, 3,
    MONS_PALE_DRACONIAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_COLD_BLOODED, 1, 1 }, },
    { "You can breathe blasts of scalding, opaque steam." },
    { "breathe steam" },
    {}, // not a starting race
} },

{ SP_DEMONSPAWN, {
    "Ds",
    "Demonspawn", "Demonic", nullptr,
    SPF_NONE,
    -1, 0, 0,
    15, 3,
    MONS_DEMONSPAWN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    8, 9, 8, // 25
    true, true, true, 4,
    {},
    {},
    {},
    { JOB_GLADIATOR, JOB_BERSERKER, JOB_ABYSSAL_KNIGHT, JOB_WIZARD,
      JOB_NECROMANCER, JOB_FIRE_ELEMENTALIST, JOB_ICE_ELEMENTALIST,
      JOB_VENOM_MAGE },
} },

{ SP_FELID, {
    "Fe",
    "Felid", "Feline", "Cat",
    SPF_NONE,
    -1, -4, 2,
    18, 6,
    MONS_FELID,
    HT_LAND, US_ALIVE, SIZE_LITTLE,
    4, 9, 11, // 24
    false, true, true, 5,
    { { MUT_CARNIVOROUS, 3, 1 }, { MUT_FAST, 1, 1 }, { MUT_FANGS, 3, 1 },
      { MUT_SHAGGY_FUR, 1, 1 }, { MUT_ACUTE_VISION, 1, 1 }, { MUT_PAWS, 1, 1 },
      { MUT_SLOW_METABOLISM, 1, 1 }, { MUT_CLAWS, 1, 1 },
      { MUT_SHAGGY_FUR, 1, 6 }, { MUT_SHAGGY_FUR, 1, 12 }, },
    { "You cannot wear armour.",
      "You are incapable of wielding weapons or throwing items." },
    { "no armour", "no weapons or thrown items" },
    { JOB_BERSERKER, JOB_ENCHANTER, JOB_TRANSMUTER, JOB_ICE_ELEMENTALIST,
      JOB_CONJURER, JOB_SUMMONER, JOB_AIR_ELEMENTALIST, JOB_VENOM_MAGE },
} },

{ SP_FORMICID, {
    "Fo",
    "Formicid", nullptr, "Ant",
    SPF_NONE,
    1, 0, 1,
    15, 4,
    MONS_FORMICID,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    12, 7, 6, // 25
    true, true, false, 4,
    { { MUT_ANTENNAE, 3, 1 }, },
    { "You are under a permanent stasis effect."
      "You can dig through walls and to a lower floor."
      "Your four strong arms can wield two-handed weapons with a shield." },
    { "permanent stasis", "dig shafts and tunnels", "four strong arms" },
    { JOB_FIGHTER, JOB_HUNTER, JOB_ABYSSAL_KNIGHT, JOB_ARCANE_MARKSMAN,
      JOB_EARTH_ELEMENTALIST, JOB_VENOM_MAGE },
} },

{ SP_GHOUL, {
    "Gh",
    "Ghoul", "Ghoulish", nullptr,
    SPF_NO_HAIR,
    0, 1, -1,
    15, 3,
    MONS_GHOUL,
    HT_LAND, US_HUNGRY_DEAD, SIZE_MEDIUM,
    11, 3, 4, // 18
    true, false, false, 5,
    { { MUT_CARNIVOROUS, 3, 1 }, { MUT_NEGATIVE_ENERGY_RESISTANCE, 3, 1 },
      { MUT_TORMENT_RESISTANCE, 1, 1 },
      { MUT_SLOW_HEALING, 1, 1 }, { MUT_COLD_RESISTANCE, 1, 1 },
      { MUT_CLAWS, 1, 1 }, { MUT_UNBREATHING, 1, 1 }, },
    { "Your body is rotting away.",
      "You thrive on raw meat." },
    { "rotting body" },
    { JOB_WARPER, JOB_GLADIATOR, JOB_MONK, JOB_NECROMANCER,
      JOB_ICE_ELEMENTALIST, JOB_EARTH_ELEMENTALIST },
} },

{ SP_GARGOYLE, {
    "Gr",
    "Gargoyle", nullptr, nullptr,
    SPF_NO_HAIR,
    0, -2, 0,
    15, 3,
    MONS_GARGOYLE,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    11, 8, 5, // 24
    true, true, false, 4,
    { { MUT_ROT_IMMUNITY, 1, 1 }, { MUT_NEGATIVE_ENERGY_RESISTANCE, 1, 1 },
      { MUT_PETRIFICATION_RESISTANCE, 1, 1 }, { MUT_SHOCK_RESISTANCE, 1, 1 },
      { MUT_UNBREATHING, 1, 1 }, { MUT_BIG_WINGS, 1, 14 }, },
    { "You are resistant to torment." },
    {},
    { JOB_FIGHTER, JOB_GLADIATOR, JOB_MONK, JOB_BERSERKER,
      JOB_FIRE_ELEMENTALIST, JOB_ICE_ELEMENTALIST, JOB_EARTH_ELEMENTALIST,
      JOB_VENOM_MAGE },
} },

{ SP_HALFLING, {
    "Ha",
    "Halfling", nullptr, nullptr,
    SPF_NONE,
    1, -1, 0,
    18, 3,
    MONS_HALFLING,
    HT_LAND, US_ALIVE, SIZE_SMALL,
    8, 7, 9, // 24
    false, false, true, 5,
    { { MUT_MUTATION_RESISTANCE, 1, 1 }, },
    {},
    {},
    { JOB_FIGHTER, JOB_HUNTER, JOB_ASSASSIN, JOB_BERSERKER, JOB_ENCHANTER,
      JOB_AIR_ELEMENTALIST },
} },

{ SP_HIGH_ELF, {
    "HE",
    "High Elf", "Elven", "Elf",
    SPF_ELVEN,
    -1, -1, 2,
    15, 4,
    MONS_ELF,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    7, 11, 10, // 28
    false, true, true, 3,
    {},
    {},
    {},
    { JOB_HUNTER, JOB_SKALD, JOB_WIZARD, JOB_CONJURER, JOB_FIRE_ELEMENTALIST,
      JOB_ICE_ELEMENTALIST, JOB_AIR_ELEMENTALIST },
} },

{ SP_HILL_ORC, {
    "HO",
    "Hill Orc", "Orcish", "Orc",
    SPF_ORCISH,
    0, 1, 0,
    15, 3,
    MONS_ORC,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, false, false, 5,
    {},
    {},
    {},
    { JOB_FIGHTER, JOB_GLADIATOR, JOB_BERSERKER, JOB_ABYSSAL_KNIGHT,
      JOB_NECROMANCER, JOB_FIRE_ELEMENTALIST },
} },

{ SP_HUMAN, {
    "Hu",
    "Human", nullptr, nullptr,
    SPF_NONE,
    1, 0, 0,
    15, 3,
    MONS_HUMAN,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    8, 8, 8, // 24
    true, true, true, 4,
    {},
    {},
    {},
    { JOB_BERSERKER, JOB_CONJURER, JOB_NECROMANCER, JOB_FIRE_ELEMENTALIST,
      JOB_ICE_ELEMENTALIST },
} },

{ SP_KOBOLD, {
    "Ko",
    "Kobold", nullptr, nullptr,
    SPF_NONE,
    1, -2, 0,
    18, 3,
    MONS_KOBOLD,
    HT_LAND, US_ALIVE, SIZE_SMALL,
    6, 6, 11, // 23
    true, false, true, 5,
    { { MUT_CARNIVOROUS, 3, 1 }, },
    {},
    {},
    { JOB_HUNTER, JOB_ASSASSIN, JOB_BERSERKER, JOB_ARCANE_MARKSMAN,
      JOB_ENCHANTER, JOB_FIRE_ELEMENTALIST, JOB_ICE_ELEMENTALIST },
} },

{ SP_MERFOLK, {
    "Mf",
    "Merfolk", "Merfolkian", nullptr,
    SPF_NONE,
    0, 0, 0,
    15, 3,
    MONS_MERFOLK,
    HT_WATER, US_ALIVE, SIZE_MEDIUM,
    8, 7, 9, // 24
    true, true, true, 5,
    {},
    { "You revert to your normal form in water.",
      "You are very nimble and swift while swimming." },
    { "change form in water", "swift swim" },
    { JOB_GLADIATOR, JOB_BERSERKER, JOB_SKALD, JOB_TRANSMUTER, JOB_SUMMONER,
      JOB_ICE_ELEMENTALIST, JOB_VENOM_MAGE },
} },

{ SP_MINOTAUR, {
    "Mi",
    "Minotaur", nullptr, nullptr,
    SPF_NONE,
    -1, 1, -2,
    12, 3,
    MONS_MINOTAUR,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    12, 5, 5, // 22
    true, false, true, 4,
    { { MUT_HORNS, 2, 1 }, },
    { "You reflexively headbutt those who attack you in melee." },
    { "retaliatory headbutt" },
    { JOB_FIGHTER, JOB_GLADIATOR, JOB_MONK, JOB_HUNTER, JOB_BERSERKER },
} },

{ SP_MUMMY, {
    "Mu",
    "Mummy", nullptr, nullptr,
    SPF_NONE,
    -1, 0, 0,
    15, 5,
    MONS_MUMMY,
    HT_LAND, US_UNDEAD, SIZE_MEDIUM,
    11, 7,  7, // 25
    false, false, false, 28, // No stat gain
    { { MUT_NEGATIVE_ENERGY_RESISTANCE, 3, 1 }, { MUT_COLD_RESISTANCE, 1, 1 },
      { MUT_TORMENT_RESISTANCE, 1, 1 },
      { MUT_UNBREATHING, 1, 1 },
      { MUT_NECRO_ENHANCER, 1, 13 }, { MUT_NECRO_ENHANCER, 1, 26 },
      { MUT_MUMMY_RESTORATION, 1, 13}, },
    { "You do not eat or drink.",
      "Your flesh is vulnerable to fire." },
    { "no food or potions", "fire vulnerability" },
    { JOB_WIZARD, JOB_CONJURER, JOB_NECROMANCER, JOB_ICE_ELEMENTALIST,
      JOB_FIRE_ELEMENTALIST, JOB_SUMMONER },
} },

{ SP_NAGA, {
    "Na",
    "Naga", nullptr, nullptr,
    SPF_SMALL_TORSO,
    0, 2, 0,
    18, 5,
    MONS_NAGA,
    HT_LAND, US_ALIVE, SIZE_LARGE,
    10, 8, 6, // 24
    true, true, true, 4,
    { { MUT_ACUTE_VISION, 1, 1 }, { MUT_SLOW, 2, 1 },  { MUT_DEFORMED, 1, 1 },
      { MUT_SPIT_POISON, 2, 1 },  { MUT_POISON_RESISTANCE, 1, 1 },
      { MUT_CONSTRICTING_TAIL, 1, 13 }, },
    { "You cannot wear boots." },
    {},
    { JOB_BERSERKER, JOB_TRANSMUTER, JOB_ENCHANTER, JOB_FIRE_ELEMENTALIST,
      JOB_ICE_ELEMENTALIST, JOB_WARPER, JOB_WIZARD, JOB_VENOM_MAGE },
} },

{ SP_OGRE, {
    "Og",
    "Ogre", "Ogreish", nullptr,
    SPF_NONE,
    0, 3, 0,
    9, 4,
    MONS_OGRE,
    HT_LAND, US_ALIVE, SIZE_LARGE,
    12, 7, 5, // 24
    true, false, false, 3,
    { { MUT_TOUGH_SKIN, 1, 1 }, },
    {},
    {},
    { JOB_HUNTER, JOB_BERSERKER, JOB_ARCANE_MARKSMAN, JOB_WIZARD,
      JOB_FIRE_ELEMENTALIST },
} },

{ SP_OCTOPODE, {
    "Op",
    "Octopode", "Octopoid", "Octopus",
    SPF_NO_HAIR,
    0, -1, 0,
    18, 3,
    MONS_OCTOPODE,
    HT_WATER, US_ALIVE, SIZE_MEDIUM,
    7, 10, 7, // 24
    true, true, true, 5,
    { { MUT_CAMOUFLAGE, 1, 1 }, { MUT_GELATINOUS_BODY, 1, 1 }, },
    { "You cannot wear most types of armour.",
      "You are amphibious." },
    { "almost no armour", "amphibious" },
    { JOB_TRANSMUTER, JOB_WIZARD, JOB_CONJURER, JOB_ASSASSIN,
      JOB_FIRE_ELEMENTALIST, JOB_ICE_ELEMENTALIST, JOB_EARTH_ELEMENTALIST,
      JOB_VENOM_MAGE },
} },

{ SP_SPRIGGAN, {
    "Sp",
    "Spriggan", nullptr, nullptr,
    SPF_NONE,
    -1, -3, 3,
    18, 7,
    MONS_SPRIGGAN,
    HT_LAND, US_ALIVE, SIZE_LITTLE,
    4, 9, 11, // 24
    false, true, true, 5,
    { { MUT_FAST, 3, 1 }, { MUT_HERBIVOROUS, 3, 1 },
      { MUT_ACUTE_VISION, 1, 1 }, { MUT_SLOW_METABOLISM, 2, 1 }, },
    {},
    {},
    { JOB_ASSASSIN, JOB_ARTIFICER, JOB_ABYSSAL_KNIGHT, JOB_WARPER,
      JOB_ENCHANTER, JOB_CONJURER, JOB_EARTH_ELEMENTALIST, JOB_VENOM_MAGE },
} },

{ SP_TENGU, {
    "Te",
    "Tengu", nullptr, nullptr,
    SPF_NO_HAIR,
    0, -2, 1,
    15, 3,
    MONS_TENGU,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    8, 8, 9, // 25
    true, true, true, 4,
    { { MUT_BEAK, 1, 1 }, { MUT_TALONS, 3, 1 },
      { MUT_TENGU_FLIGHT, 1, 5 }, { MUT_TENGU_FLIGHT, 1, 14 }, },
    {},
    {},
    { JOB_BERSERKER, JOB_WIZARD, JOB_CONJURER, JOB_SUMMONER,
      JOB_FIRE_ELEMENTALIST, JOB_AIR_ELEMENTALIST, JOB_VENOM_MAGE },
} },

{ SP_TROLL, {
    "Tr",
    "Troll", "Trollish", nullptr,
    SPF_NONE,
    -1, 3, -2,
    9, 3,
    MONS_TROLL,
    HT_LAND, US_ALIVE, SIZE_LARGE,
    15, 4, 5, // 24
    true, false, false, 3,
    { { MUT_TOUGH_SKIN, 2, 1 }, { MUT_REGENERATION, 2, 1 }, { MUT_CLAWS, 3, 1 },
      { MUT_GOURMAND, 1, 1 }, { MUT_FAST_METABOLISM, 3, 1 },
      { MUT_SHAGGY_FUR, 1, 1 }, },
    {},
    {},
    { JOB_FIGHTER, JOB_MONK, JOB_HUNTER, JOB_BERSERKER, JOB_WARPER,
      JOB_EARTH_ELEMENTALIST, JOB_WIZARD },
} },

{ SP_VAMPIRE, {
    "Vp",
    "Vampire", "Vampiric", nullptr,
    SPF_NONE,
    -1, 0, 0,
    18, 4,
    MONS_VAMPIRE,
    HT_LAND, US_SEMI_UNDEAD, SIZE_MEDIUM,
    7, 10, 9, // 26
    false, false, false, 28, // No stat gain
    { { MUT_FANGS, 3, 1 }, { MUT_ACUTE_VISION, 1, 1 },
      { MUT_UNBREATHING, 1, 1 }, },
    {},
    {},
    { JOB_MONK, JOB_ASSASSIN, JOB_ENCHANTER, JOB_EARTH_ELEMENTALIST,
      JOB_NECROMANCER, JOB_ICE_ELEMENTALIST },
} },

{ SP_VINE_STALKER, {
    "VS",
    "Vine Stalker", "Vine", "Vine",
    SPF_NONE,
    0, -3, 1,
    15, 5,
    MONS_VINE_STALKER,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    10, 8, 9, // 27
    true, false, true, 4,
    { { MUT_FANGS, 2, 1 }, { MUT_FANGS, 1, 8 },
      { MUT_MANA_SHIELD, 1, 1 }, { MUT_ANTIMAGIC_BITE, 1, 1 },
      { MUT_SHAGGY_FUR, 1, 1 }, { MUT_ROT_IMMUNITY, 1, 1 },
      { MUT_NO_DEVICE_HEAL, 3, 1 },
      { MUT_REGENERATION, 1, 1 }, { MUT_REGENERATION, 1, 6 },
      { MUT_REGENERATION, 1, 12 }, },
    {},
    {},
    { JOB_MONK, JOB_ASSASSIN, JOB_ENCHANTER, JOB_CONJURER, JOB_NECROMANCER,
      JOB_AIR_ELEMENTALIST, JOB_ICE_ELEMENTALIST },
} },
#if TAG_MAJOR_VERSION == 34
{ SP_SLUDGE_ELF, {
    "SE",
    "Sludge Elf", "Elven", "Elf",
    SPF_ELVEN,
    0, -1, 1,
    15, 3,
    MONS_ELF,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    8, 8, 8, // 24
    false, true, true, 4,
    {},
    {},
    {},
    {}, // not a starting race
} },

{ SP_LAVA_ORC, {
    "LO",
    "Lava Orc", "Orcish", "Orc",
    SPF_ORCISH | SPF_NO_HAIR,
    -1, 1, 0,
    15, 3,
    MONS_LAVA_ORC,
    HT_AMPHIBIOUS_LAVA, US_ALIVE, SIZE_MEDIUM,
    10, 8, 6, // 24
    true, false, false, 5,
    {},
    {},
    {},
    {}, // not a starting race
} },

{ SP_DJINNI, {
    "Dj",
    "Djinni", "Djinn", nullptr,
    SPF_NONE,
    -1, -1, 0,
    9, 3,
    MONS_DJINNI,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    8, 8, 8, // 24
    true, true, true, 4,
    { { MUT_NEGATIVE_ENERGY_RESISTANCE, 3, 1 }, },
    { "You are immune to all types of fire, even holy and hellish.",
      "You are vulnerable to cold.",
      "You need no food.",
      "You have no legs." },
    { "fire immunity", "cold vulnerability" },
    {}, // not a starting race
} },
#endif
// Ideally this wouldn't be necessary...
{ SP_UNKNOWN, {
    "??",
    "Yak", nullptr, nullptr,
    SPF_NONE,
    0, 0, 0,
    0, 0,
    MONS_PROGRAM_BUG,
    HT_LAND, US_ALIVE, SIZE_MEDIUM,
    0, 0, 0, // 0
    false, false, false, 28,
    {},
    {},
    {},
    {},
} }
};
