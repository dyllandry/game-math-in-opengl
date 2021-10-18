#!/bin/bash

gcc src/main.c lib/glad.c -o bin/main -lglfw -lGL -ldl

