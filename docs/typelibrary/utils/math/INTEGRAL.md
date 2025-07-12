# INTEGRAL

![INTEGRAL](https://github.com/user-attachments/assets/36f8dda0-26f0-45e1-b601-af9b29905109)

* * * * * * * * * *
## Einleitung
Der Funktionsblock INTEGRAL berechnet näherungsweise das Integral über die Zeit. Er summiert dabei alle Teilintegrale (Eingangswert * Zeitdifferenz) auf. Der Block ist besonders nützlich für Anwendungen, bei denen kontinuierliche Werte über die Zeit integriert werden müssen, wie z.B. bei der Berechnung von Energieverbräuchen oder Flächen unter Kurven.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die normale Ausführung des Blocks. Verknüpft mit den Daten-Eingängen IN und TM.
- **RESET**: Setzt den Ausgang OUT auf null und OVERFLOW auf FALSE. Wird verwendet, um den Block zurückzusetzen.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die Ausführung des Blocks. Verknüpft mit den Daten-Ausgängen OUT und OVERFLOW.

### **Daten-Eingänge**
- **IN** (REAL, Initialwert: 0.0): Der Eingangswert, der integriert werden soll.
- **TM** (DINT, Initialwert: 0): Die Zeit seit dem letzten Aufruf in Millisekunden.

### **Daten-Ausgänge**
- **OUT** (REAL, Initialwert: 0.0): Der Wert des Integrals, berechnet durch Summierung aller Teilintegrale (IN * TM).
- **OVERFLOW** (BOOL, Initialwert: FALSE): TRUE, wenn der Wert von OUT den Bereich der REAL-Variablen überschreitet. Der Block wird blockiert, bis er durch RESET neu initialisiert wird.

## Funktionsweise
Der Block berechnet das Integral, indem er den Eingangswert IN mit der Zeitdifferenz TM multipliziert und das Ergebnis zum aktuellen Wert von OUT addiert. Die Zeitdifferenz wird in Sekunden umgerechnet (Division durch 1000.0). Falls das Ergebnis den zulässigen Bereich für REAL-Variablen überschreitet, wird OVERFLOW auf TRUE gesetzt und die Berechnung gestoppt. Ein RESET-Ereignis setzt OUT auf 0.0 und OVERFLOW auf FALSE zurück.

## Technische Besonderheiten
- Der Block überprüft auf Überlauf (OUT > 1.0E38 oder OUT < -1.0E38) und setzt in diesem Fall OVERFLOW auf TRUE.
- Die Zeitdifferenz TM muss positiv sein (TM > 0), damit eine Berechnung erfolgt.
- Der Block ist inspiriert von der CODESYS-Bibliothek "Util/Mathematical-Functions/INTEGRAL".

## Zustandsübersicht
- **REQ**: Führt die normale Integrationsberechnung durch.
- **RESET**: Setzt den Block zurück (OUT = 0.0, OVERFLOW = FALSE).

## Anwendungsszenarien
- Berechnung der Gesamtenergie aus Leistungsmesswerten über die Zeit.
- Integration von Geschwindigkeitsdaten zur Berechnung der zurückgelegten Strecke.
- Flächenberechnung unter Kurven in Echtzeit.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu einfachen Summierungsblöcken berücksichtigt INTEGRAL die Zeitdifferenz zwischen den Aufrufen, was für dynamische Systeme essenziell ist.
- Ähnliche Blöcke in anderen Bibliotheken (z.B. CODESYS) bieten vergleichbare Funktionalität, aber INTEGRAL ist speziell für die 4diac-Umgebung optimiert.

## Fazit
Der INTEGRAL-Block ist ein leistungsfähiges Werkzeug zur näherungsweisen Berechnung von Integralen über die Zeit. Durch die Überlaufprüfung und die Möglichkeit zurücksetzen zu können, ist er robust und vielseitig einsetzbar. Besonders in Echtzeitanwendungen, bei denen kontinuierliche Daten integriert werden müssen, ist dieser Block eine wertvolle Ergänzung.
