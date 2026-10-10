# Cryptography and Network Security (CNS) Lab - Questions 1-40

This repository contains **40 separately runnable C programs**, ordered to match the supplied CNS lab PDF, plus written answers, example outputs, a GitHub Actions compile workflow, and a GitHub Codespaces setup.

## Files in this project

- `q01_*.c` through `q40_*.c` - one C source file for each numbered lab question.
- `ANSWERS_AND_EXPLANATIONS.md` - written answers, formulas, assumptions, and important notes for all 40 questions.
- `CNS_LIST_OF_PROGRAMS_SOURCE.pdf` - copy of the supplied assignment PDF.
- `run_question.sh` - compile and run one selected question.
- `Makefile` - compile all questions with one command.
- `.github/workflows/compile-c.yml` - GitHub Actions workflow that compiles all programs on every push and pull request, then checks known S-DES/RSA outputs.
- `.devcontainer/devcontainer.json` - Codespaces environment setup.
- `cryptoutils.h`, `des_schedule.h`, `sdes.h` - small shared helper headers for relevant questions.

## Recommended workflow: push to GitHub, then run in the browser

### Step 1 - Download and extract

Download `cryptography-c-lab.zip` and extract it. Keep the folder structure, especially the hidden `.github` and `.devcontainer` folders.

### Step 2 - Create a GitHub repository

1. Sign in to [GitHub](https://github.com/).
2. Click **+** (top-right) -> **New repository**.
3. Name it `cryptography-c-lab` (or another name).
4. Choose Public or Private.
5. Create an **empty** repository. Do not add a README because this ZIP already contains one.

### Step 3 - Push the extracted project

The most reliable way to keep all 40 files and hidden folders is Git from a terminal. Install Git if needed, open a terminal inside the extracted `cryptography-c-lab` folder, and run the following commands. Replace `YOUR-USERNAME` with your GitHub username and use the repository name you created.

```bash
git init
git add .
git commit -m "Add all 40 CNS cryptography lab programs"
git branch -M main
git remote add origin https://github.com/YOUR-USERNAME/cryptography-c-lab.git
git push -u origin main
```

If Git says your email/name is not configured, run `git config --global user.name "Your Name"` and `git config --global user.email "YOUR-EMAIL"`, then repeat the commit and push. GitHub may ask you to authenticate in a browser.

### Step 4 - Confirm automatic compilation

Open the repository on GitHub and select the **Actions** tab. The workflow starts after the push. Open the latest run:

- Green check: all 40 source files compiled and the included known-answer smoke tests passed.
- Red cross: open the run and inspect the first compiler/test error in its logs.

The workflow checks compilation and selected sample outputs. It does **not** interactively type input for every program.

### Step 5 - Run a question in GitHub Codespaces

1. Open your repository on GitHub.
2. Click the green **Code** button.
3. Select **Codespaces** -> **Create codespace on main**.
4. Wait for the VS Code-like browser editor to open.
5. Choose **Terminal** -> **New Terminal**.
6. Run one question using `bash run_question.sh NUMBER`.

Examples:

```bash
bash run_question.sh 1
bash run_question.sh 3
bash run_question.sh 9
bash run_question.sh 22
bash run_question.sh 33
bash run_question.sh 40
```

Enter your input when the program prompts you. Codespaces is the interactive place to enter keys and messages; GitHub Actions is the automatic build checker.

## Compile and run commands

Run a single program:

```bash
bash run_question.sh 12
```

Compile all 40 programs:

```bash
make all
```

After `make all`, compiled executables are in `build/`. For example, run Question 24 with:

```bash
./build/q24_rsa_private_key
```

Remove compiled executables:

```bash
make clean
```

The `run_question.sh` helper requires GCC and the OpenSSL development library (needed by the AES and DES demonstrations). The provided Codespaces configuration installs `libssl-dev`; the GitHub Actions workflow installs `build-essential` and `libssl-dev`.

## Program index

| Q | Source file | Topic |
|---:|---|---|
| 1 | `q01_caesar.c` | Caesar cipher |
| 2 | `q02_monoalphabetic.c` | Monoalphabetic substitution |
| 3 | `q03_playfair.c` | Playfair cipher |
| 4 | `q04_vigenere.c` | Vigenere / polyalphabetic substitution |
| 5 | `q05_affine.c` | Affine Caesar cipher |
| 6 | `q06_affine_frequency_attack.c` | Affine cipher frequency attack |
| 7 | `q07_substitution_cryptogram.c` | Symbol frequency analysis and substitution cryptogram |
| 8 | `q08_keyword_substitution.c` | Keyword-derived substitution alphabet |
| 9 | `q09_pt109_playfair_decrypt.c` | PT-109 Playfair decryption |
| 10 | `q10_fixed_playfair.c` | Encrypt with the supplied Playfair matrix |
| 11 | `q11_playfair_keyspace.c` | Playfair keyspace estimate |
| 12 | `q12_hill_cipher.c` | Hill cipher encrypt/decrypt |
| 13 | `q13_hill_known_plaintext_attack.c` | Recover a 2x2 Hill key from known pairs |
| 14 | `q14_one_time_pad_vigenere.c` | Given numeric Vigenere key stream |
| 15 | `q15_additive_frequency_attack.c` | Additive cipher frequency attack, top 10 |
| 16 | `q16_monoalphabetic_frequency_attack.c` | Monoalphabetic substitution heuristic attack |
| 17 | `q17_des_reverse_subkeys.c` | DES subkey generation and reverse decryption order |
| 18 | `q18_des_subkey_halves.c` | DES 48-bit subkey halves |
| 19 | `q19_cbc_aes.c` | AES-256-CBC demonstration |
| 20 | `q20_ecb_cbc_error_propagation.c` | ECB/CBC error propagation explanation |
| 21 | `q21_padding_demo.c` | 1-then-zero bit padding demonstration |
| 22 | `q22_sdes_cbc.c` | S-DES in CBC mode |
| 23 | `q23_sdes_ctr.c` | S-DES in counter mode |
| 24 | `q24_rsa_private_key.c` | Factor n and calculate RSA private exponent |
| 25 | `q25_rsa_common_factor.c` | RSA common-factor demonstration |
| 26 | `q26_rsa_key_reuse.c` | RSA key compromise explanation |
| 27 | `q27_rsa_small_alphabet_attack.c` | Brute-force raw RSA over alphabet-sized messages |
| 28 | `q28_diffie_hellman.c` | Diffie-Hellman shared key demonstration |
| 29 | `q29_sha3_capacity_lanes.c` | SHA-3 rate/capacity lane explanation |
| 30 | `q30_cbc_mac_forgery.c` | CBC-MAC length-extension illustration |
| 31 | `q31_cmac_subkeys.c` | CMAC K1/K2 generation constants and shifts |
| 32 | `q32_dsa_nonce_demo.c` | DSA nonce/signature demonstration |
| 33 | `q33_des_full.c` | DES single-block encrypt/decrypt using OpenSSL |
| 34 | `q34_padding_demo.c` | Repeated padding question |
| 35 | `q35_otp_vigenere_stream.c` | Interactive one-time-pad Vigenere stream |
| 36 | `q36_affine_duplicate.c` | Repeated affine cipher question |
| 37 | `q37_monoalphabetic_attack.c` | Repeated monoalphabetic attack question |
| 38 | `q38_hill_attack_duplicate.c` | Repeated Hill known-plaintext attack |
| 39 | `q39_additive_attack_duplicate.c` | Repeated additive cipher attack |
| 40 | `q40_monoalphabetic_attack_duplicate.c` | Repeated monoalphabetic attack question |

## Important educational notes

- The list repeats questions 21/34, 5/36, 16/37/40, 13/38, and 15/39. They have separate source files to match the PDF numbering.
- Frequency-analysis programs produce ranked guesses; they cannot guarantee that arbitrary ciphertext will be solved correctly. Question 7 additionally prints the known Gold-Bug cryptogram solution.
- The S-DES examples in Questions 22 and 23 reproduce the handout's stated test outputs.
- DES, toy RSA parameters, fixed demonstration keys/IVs, and the toy CBC-MAC cipher are for coursework only. Do not use these demonstrations to protect real data.
- See `ANSWERS_AND_EXPLANATIONS.md` for formulas and written responses, including the theory parts of the PDF questions.
