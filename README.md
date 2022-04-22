# FEUP-DA-PROJ1

## First project for the DA course unit at FEUP.

The main task of this work is to implement a system capable of managing a modern urban delivery system.

## Building

This project uses [cmake](https://cmake.org/). Assuming it's installed and properly setup, simply run:

1. `cmake -S . -B build` in this project's directory to generate the build system.
2. To build the project's documentation, run `cmake --build build --target documentacao`.
3. To build the project's executable, run `cmake --build build --config Release --target logistics`. Following that, the executable can be found under the `build/codigo/` directory, named `logistics`.

## Running

Simply run the executable generated in the last section. Don't forget to put your data files in a folder named `input`.

## Unit info

* **Name**: Desenho de Algoritmos (Algorithm Design)
* **Date**: Year 2, Semester 2, 2021/22
* [**More info**](https://sigarra.up.pt/feup/pt/ucurr_geral.ficha_uc_view?pv_ocorrencia_id=484424)

## Disclaimer

This repository is for archival and educational purposes only.

If you don't understand some part of the code or anything else in this repo, feel free to ask (although I may not understand it myself anymore).

Keep in mind that this repo is public. If you copy any code and use it in your school projects you may be flagged for plagiarism by automated tools.
