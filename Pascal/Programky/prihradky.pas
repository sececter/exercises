program prihradky;

uses libSeznam;

const  M = 26;

var 
	jmena : seznam;
	pismeno : char;
	x : uPrvek;
	P : array[char] of seznam;
	i : char;

begin
jmena.init; new(x);
jmena := seznamZeSouboru('jmena');
for i:='A' to 'Z' do P[i].init;
x := jmena.hlava;

while x^.dalsi<>nil do begin
	pismeno := x^.data[1];
	P[pismeno].vlozNaKonec(x^.data);
	x := x^.dalsi;
end;
for i := 'A' to 'Z' do begin
	x:=P[i].vyjmiPrvni;
	while x^.dalsi<>nil do begin
		writeln(x^.data);
		x := P[i].vyjmiPrvni;
	end;
end;
end.
