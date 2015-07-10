unit libSeznam;

interface
type
	data = integer;
	uPrvek = ^Prvek;
	Prvek = record
		data : data;
		dalsi : uPrvek;
	end;
	Seznam = object
		hlava, konec : uPrvek;
		constructor init;
		function vyjmiPrvni : uPrvek;
		function nty(kolikaty : integer) : uPrvek;
		procedure vlozNaKonec(var co : data);
		procedure vlozNaZacatek(var co : data);
		procedure vlozZa(p : uPrvek; var co : data);
		procedure vlozNamisto(p : uPrvek; var co : data);
		procedure smazZa(p : uPrvek);
		procedure smaz(p : uPrvek);
		procedure prohod(var p1,p2 : uPrvek);
		procedure vypsat;
		function velikost : integer;
		function kolikaty(ktery : uPrvek) : integer;
	end;
	
function seznamZeSouboru(jmenoS : string) : seznam;

implementation

{----------------------------metody seznamu----------------------------}
constructor Seznam.init;
begin
	new(hlava);
	konec := hlava;
	hlava^.dalsi := nil;
end;

procedure Seznam.vlozNaKonec(var co : data);
begin
konec^.data := co;
new(konec^.dalsi);
konec := konec^.dalsi;
konec^.dalsi := nil;
end;

procedure Seznam.vlozNaZacatek(var co : data);
var pom : uPrvek;
begin
new(pom);
pom^.data := co;
pom^.dalsi := hlava;
hlava := pom;
end;

function Seznam.vyjmiPrvni : uPrvek;
var pom : uPrvek;
begin
	pom := hlava;
	hlava:=pom^.dalsi;
	vyjmiPrvni := pom;
end;

function Seznam.nty(kolikaty : integer) : uPrvek;
var 
	pom : uPrvek;
	i : integer;
begin
	pom := hlava;
	i := 1;
	while i<>kolikaty do begin
		inc(i);
		pom := pom^.dalsi;
	end;
	nty := pom;
end;

procedure Seznam.vlozZa(p : uPrvek; var co : data);
var novy : uPrvek;
begin
new(novy);
novy^.data := co;
novy^.dalsi := p^.dalsi;
p^.dalsi := novy;
end;

procedure Seznam.vlozNamisto(p : uPrvek; var co : data);
begin
	Seznam.vlozZa(p, p^.data);
	p^.data:=co;
end;

procedure Seznam.smazZa(p : uPrvek);
var q : uPrvek;
begin
	q := p^.dalsi;
	p^.dalsi := p^.dalsi^.dalsi;
	dispose(q);
end;

procedure Seznam.smaz(p : uPrvek);
begin
	if p^.dalsi <> konec then begin
		p^.data := p^.dalsi^.data;
		smazZa(p);
	end
	else begin
		dispose(konec);
		konec:=p;
		konec^.dalsi := nil;
	end;
end;

procedure Seznam.prohod(var p1,p2 : uPrvek);
var pom : Prvek;
begin
pom.data := p2^.data;
p2^.data := p1^.data;
p1^.data := pom.data;
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

function Seznam.velikost : integer;
var 
	pom : uPrvek;
	i : integer;
begin
pom := hlava;
i := 1;
while pom^.dalsi <> konec do begin
	inc(i);
	pom := pom^.dalsi;
end;
velikost := i;
end;

function Seznam.kolikaty(ktery : uPrvek) : integer;
var
	i : integer;
	x : uPrvek;
begin
	new(x);
	x := hlava;
	i:=1;
	while x<>ktery do begin x:=x^.dalsi; inc(i); end;
	kolikaty:=i;
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
