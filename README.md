# COFF

Offline Judge for Competitive Coding 

---

# How to run this Project?

1) Clone the Repository.
2) Switch to `master` branch.
3) To build the project, enter `make`.
4) Run `./coff` .
5) To remove the program compiled in step 3, enter `make clean` .

---

# Start with Coff

As soon as a person builds Coff using `make`, an example question is saved to
`~/coff/quest` directory, with name __"example1.quest"__ .

You can see the question by running:

```shell
./coff -s example1.quest
```

Write a program for it and save it `~/coff/ans`. Lets say you made __"1.c"__.
Type:

```shell
./coff -q example1.quest -l c -t 1.c
```

All program files must be saved inside `~/coff/ans` or as in the path specified
in configuration file, else provide full path to your profram.

One can also find sample C/C++, Python and Javascript programs which were used
in testing of Coff. They are in `test_programs/` directory.

---

# How to write questions?

1) Follow till Step 2 of *"How to run this Project?"*
2) Enter `make coff-quest`.
3) Run `./coff-quest`.
4) To remove the program compiled in step 2, enter `make clean`.

---

# How to reset configuration file?

1) Run `make coff-config`.

---

# Documentation

To see user, documentation, run:

```shell
./coff -d
```

or

```shell
./coff --doc
```

---

# Core Developers/ Contributors

1) [Shikhar Kataruka](https://github.com/shikhar9820)
2) [Shivam Khurana](https://github.com/SeeBoom)
3) [Shreya Sneha](https://github.com/shreyasneha29)
4) [Vaibhav Gupta](https://github.com/VARoDeK)

---
