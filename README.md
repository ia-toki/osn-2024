[![tutorial-osn-workflow](https://img.shields.io/badge/tutorial--link--of-osn--workflow-blue.svg)](https://github.com/ia-toki/osn-2024/blob/master/WORKFLOW.md)
[![tutorial-git](https://img.shields.io/badge/tutorial--link--of-git-green.svg)](https://about.gitlab.com/images/press/git-cheat-sheet.pdf)

# OSN 2024 Problem Repository

Problem repository of **OSN 2024** (also known internationally as **TOKI Indonesian NOI Open Contest 2024**).

## Problems

| Alias | Slug                  | Title (id)            | Title (en)               | Type        |
| ----- | --------------------- | --------------------- | ------------------------ | ----------- |
| 0A    | `osn-2024-histori`    | Riwayat Bebek         | Duck History             | Batch       |
| 0B    | `osn-2024-harta`      | Harta Karun Nasional  | National Treasure        | Interactive |
| 0C    | `osn-2024-mosaik`     | Mosaik Monokrom       | Monochrome Mosaic        | Output-Only |
| 1A    | `osn-2024-pusat`      | Pemerintahan Pusat    | Central Government       | Batch       |
| 1B    | `osn-2024-rotasi`     | Pertahanan Batavia    | Batavia Defense          | Batch       |
| 1C    | `osn-2024-batik`      | Batik Betawi          | Betawi Batik             | Batch       |
| 2A    | `osn-2024-macet`      | Mobil Manual          | Manual Car               | Batch       |
| 2B    | `osn-2024-krl`        | Kereta Rel Listrik    | Electric Railway Trains  | Batch       |
| 2C    | `osn-2024-mikroba`    | Mikroba Ciliwung      | Ciliwung Microbes        | Interactive |

## Credits

| Alias | Slug                  | Problem Author(s)                         | Developer(s)                              |
| ----- | --------------------- | ----------------------------------------- | ----------------------------------------- |
| 0A    | `osn-2024-histori`    | Ammar Fathin Sabili                       | Ammar Fathin Sabili                       |
| 0B    | `osn-2024-harta`      | I Nyoman Narayan Kitas Utama              | Ammar Fathin Sabili                       |
| 0C    | `osn-2024-mosaik`     | Ahmad Zaky                                | Ammar Fathin Sabili                       |
| 1A    | `osn-2024-pusat`      | Mushthofa                                 | Christoffer Edbert Karuniawan             |
| 1B    | `osn-2024-rotasi`     | Maximilliano Utomo Quok                   | Maximilliano UQ, Pikatan AB, Wahyono      |
| 1C    | `osn-2024-batik`      | Pikatan Arya Bramajati                    | Pikatan Arya Bramajati                    |
| 2A    | `osn-2024-macet`      | Pikatan Arya Bramajati                    | Andrew                                    |
| 2B    | `osn-2024-krl`        | Ashar Fuadi                               | Yohandi                                   |
| 2C    | `osn-2024-mikroba`    | Ammar Fathin Sabili                       | Ammar Fathin Sabili                       |

Maximilliano Utomo Quok and Mushthofa also developed unpublished (backup) problems.

## Upsolving and Editorial

The problem statements and upsolving are available [on TLX](https://tlx.toki.id/problems/osn-2024).

The editorial can also be found on the same link.

## Problem Structure Repository

Each problem contains a problem directory root.

A problem directory root contains the following files and directories:

* ID problem description (`description-id.html`)
* EN problem description (`description-en.html`)
* Model solution (`solution.cpp`)
* Subtasks solution (`solution-<subtask-number>.cpp`)
* Test case generator (`spec.cpp`)
* Configuration file (`config.json`)
* Alternative solutions (`solution-<author>-<verdict>-<solution-name>.cpp`)
* Render directory (`render/`)
* Helper directory (`helper/`)
* Communicator (`communicator.cpp`)
* Output validator (`scorer.cpp`)

### ID problem description

Problem description in Bahasa Indonesia. The HTML file uses [Katex](https://katex.org/) syntax to render the math equations. There is a [description header](https://github.com/ia-toki/osn-2024/blob/master/utils/description_header.html) file in `utils/` to render the preview.

### EN problem description

Problem description in the English language.

### Model solution

The solution used to generate the test cases.

### Subtasks solution

Solutions that are used to test the subtasks.

### Test case generator

Test case generator using [tcframe](http://tcframe.toki.id/en/stable/) 1.6.0.

### Configuration file

A JSON object that may help with the automation of choosing the correct settings in online judges. There is a [config script](https://github.com/ia-toki/osn-2024/blob/master/utils/config.js) file in `utils/` to configure the test data files automatically.

Possible configs in this file:

* `time_limit` (number in ms)
* `memory_limit` (number in kB)
* `samples` (a list of lists that maps a sample to its subtasks)
* `test_groups` (a list of lists that maps the test group to its subtasks)
* `points` (a list containing the points of each subtask)
* `interactive` (a boolean)

### Alternative solutions

Several alternative and incorrect solutions for testing.

### Render directory

The assets (usually images) that are used by the HTML description file.

### Helper directory

Scripts that may help with problem preparation or the raw files of the assets in `render/`.

### Communicator

For communication in interactive problems using [tcframe format](https://tcframe.toki.id/en/stable/topic-guides/styles.html#communicator).

### Output validator

To validate solutions that do not use exact match (may contain multiple solutions or require precision handling) using [tcframe format](https://tcframe.toki.id/en/stable/topic-guides/styles.html#scorer).

## License

All tasks and materials are published under the [Creative Commons Attribution (CC-BY)](https://github.com/ia-toki/osn-2024/blob/master/LICENSE) License.
