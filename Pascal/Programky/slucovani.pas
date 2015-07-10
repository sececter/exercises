program slucovani;

uses libSeznam;

var A : seznam;

function sloucit(A : seznam; B : seznam) : seznam;
var
	ap,bp : uPrvek;
	C : seznam;
begin
	C.init;
	ap := A.vyjmiPrvni; bp := B.vyjmiPrvni;
	while (ap<>A.konec) and (bp<>B.konec) do
	if ap^.data < bp^.data then begin C.vlozNaKonec(ap^.data); ap := A.vyjmiPrvni; end
		else begin C.vlozNaKonec(bp^.data); bp := B.vyjmiPrvni; end;
	if ap = A.konec then while bp^.dalsi<>nil do begin C.vlozNaKonec(bp^.data); bp:=bp^.dalsi; end;
	if bp = B.konec then while ap^.dalsi<>nil do begin C.vlozNaKonec(ap^.data); ap:=ap^.dalsi; end;
	sloucit := C;
end;

function setriditSlucovanim(A : seznam) : seznam;
var
	B,C : seznam;
	n,i : integer;
	x : uPrvek;
begin
	n := A.velikost;
	if n>1 then begin
		B.init; C.init; new(x);
		for i:=1 to (n div 2) do B.vlozNaKonec(A.vyjmiPrvni^.data);
		x:=A.hlava;
		while x^.dalsi<>nil do begin C.vlozNaKonec(A.vyjmiPrvni^.data); x:=x^.dalsi; end;
		setriditSlucovanim := sloucit(setriditSlucovanim(B),setriditSlucovanim(C));
	end
	else setriditSlucovanim := A;
end;

begin
A.init;
A := seznamZeSouboru('data');
A := setriditSlucovanim(A);
A.vypsat;
end.
