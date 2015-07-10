unit libObSeznam;

interface
type
	data = integer;
	uPrvek = ^Prvek;
	Prvek = record
		data : data;
		predchozi, dalsi : uPrvek;
	end;
	Seznam = object
		hlava,konec : uPrvek;
		constructor init;
		procedure vlozNaKonec(var co : data);
		procedure prohod(p1,p2 : uPrvek);
		procedure vypsat;
	end;
	function seznamZeSouboru(jmenoS : string) : seznam;

implementation

{----------------------------metody seznamu----------------------------}
constructor Seznam.init;
begin
	new(hlava);
	konec := hlava;
	hlava^.dalsi := nil;
	konec^.predchozi := nil;
end;

procedure Seznam.vlozNaKonec(var co : data);
var pom : uPrvek;
begin
konec^.data := co;
new(konec^.dalsi);
new(pom);
pom :=konec;
konec := konec^.dalsi;
konec^.dalsi := nil;
konec^.predchozi := pom;
end;

procedure Seznam.prohod(p1,p2 : uPrvek);
var pom : uPrvek;
begin
new(pom);
pom^.data := p1^.data;
p1^.data := p2^.data;
p2^.data := pom^.data;
dispose(pom);
end;

procedure Seznam.vypsat;
var pom : uPrvek;
begin
pom := hlava;
while pom^.dalsi<>nil do begin
	writeln(pom^.data);
	pom:=pom^.dalsi;
end;
end;

{----------------------------------------------------------------------}
function seznamZeSouboru(jmenoS : string) : seznam;
var 
	userFile : text;
	d : data;
	sez : seznam;
begin
sez.init;
assign(userFile, jmenoS);
reset(userFile);
repeat
	readln(userFile, d);
	sez.vlozNaKonec(d);
until eof(userFile);
close(userFile);
seznamZeSouboru := sez;
end;

end.
