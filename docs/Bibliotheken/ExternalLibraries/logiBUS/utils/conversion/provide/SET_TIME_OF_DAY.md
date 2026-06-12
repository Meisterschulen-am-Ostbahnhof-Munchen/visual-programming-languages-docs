# SET_TIME_OF_DAY


![SET_TIME_OF_DAY](./SET_TIME_OF_DAY.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `SET_TIME_OF_DAY` dient dazu, einen über den Dateneingang `IN` bereitgestellten Tageszeitwert in eine als InOut-Variable deklarierte Zielvariable `OUT` zu schreiben. Der Baustein ist als einfacher FB (SimpleFB) realisiert und entspricht der Norm IEC 61499-1.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Normaler Ausführungsanforderung (gebunden an `IN` und `OUT`) |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung der Ausführung (gebunden an `OUT`) |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| IN   | TIME_OF_DAY | Der zu schreibende Tageszeitwert |

### **Daten-Ausgänge**
Keine expliziten Daten-Ausgänge vorhanden. Die Zielgröße wird als InOut-Variable geführt.

### **Adapter**
Keine.

## Funktionsweise
Beim Eintreffen eines Ereignisses am Eingang `REQ` wird der Algorithmus `REQ` ausgeführt:
- Der Wert von `IN` wird der InOut-Variable `OUT` zugewiesen: `OUT := IN`.
- Nach erfolgreicher Zuweisung wird das Ereignis `CNF` ausgegeben, um den Abschluss der Operation zu quittieren.

## Technische Besonderheiten
- Die Zielvariable `OUT` ist als **InOut-Variable** deklariert. Dies bedeutet, dass sie sowohl als Eingabe als auch als Ausgabe dient und von außen als Referenz übergeben werden muss. Der Wert von `OUT` wird durch die Zuweisung überschrieben.
- Der Baustein enthält nur einen Zustand und einen Algorithmus, was eine sehr einfache, deterministische Ausführung gewährleistet.
- Der Datentyp `TIME_OF_DAY` folgt der IEC 61499-Datentypdefinition für Tageszeiten (z. B. `TOD#12:30:00`).

## Zustandsübersicht
Der Baustein besitzt einen einzigen Zustand:
- **REQ**: Wird beim Event `REQ` aktiviert. Nach Ausführung des Algorithmus wird `CNF` gesendet und der Zustand bleibt aktiv (kein Zustandswechsel).

| Zustand | Aktion | Ausgangsereignis |
|---------|--------|------------------|
| REQ     | Algorithmus `REQ` | CNF |

## Anwendungsspezifische Szenarien
- **Setzen einer globalen Tageszeit**: In einer Steuerung kann die aktuelle Uhrzeit von einem übergeordneten System übernommen und in eine zentrale InOut-Variable geschrieben werden.
- **Konfiguration von Zeitparametern**: Ein Benutzer gibt über eine HMI eine Tageszeit ein, die dann mit `SET_TIME_OF_DAY` in eine Konfigurationsvariable geschrieben wird.
- **Weitergabe von Zeitwerten**: Wenn ein Zeitwert aus einer Quelle gelesen und an mehrere Nachfolgebausteine weitergegeben werden muss, kann dieser FB als einfacher Schreibzugriff dienen.

## Vergleich mit ähnlichen Bausteinen
- **MOVE für elementare Typen**: Ähnliche Bausteine existieren für Basistypen wie `BOOL`, `INT`, `REAL` etc. `SET_TIME_OF_DAY` ist die spezifische Variante für `TIME_OF_DAY`.
- **Standard-MOVE-Bausteine**: In vielen IEC-61499-Bibliotheken gibt es generische `MOVE`- oder `ASSIGN`-Funktionsbausteine. Der vorgestellte Baustein ist eine dedizierte und typsichere Umsetzung für `TIME_OF_DAY`.

## Fazit
`SET_TIME_OF_DAY` ist ein minimaler, aber nützlicher Funktionsbaustein zum Überschreiben einer `TIME_OF_DAY`-InOut-Variablen. Seine einfache Struktur macht ihn zuverlässig und leicht verständlich. In Kombination mit anderen Bausteinen kann er in Zeitsteuerungs- und Konfigurationsanwendungen effektiv eingesetzt werden.