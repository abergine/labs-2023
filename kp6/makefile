all: convert gen_db


convert: convert.o db.o
	gcc convert.o db.o -o convert

gen_db: gen_db.c db.c
	gcc gen_db.c db.c -o gen_db

convert.o: convert.c
	gcc convert.c -c -o convert.o

db.o: db.c
	gcc db.c -c -o db.o