# SUM


![SUM](./SUM.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **SUM** ermöglicht die Berechnung der Summe aller Elemente eines dynamischen Arrays. Er wird durch ein Ereignis am Eingang REQ angestoßen und gibt nach erfolgreicher Berechnung das Ergebnis über den Datenausgang sowie ein Bestätigungsereignis über CNF aus.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Beschreibung |
|------|--------------|
| REQ  | Startet die Summenberechnung des Arrays A. |

### **Ereignis-Ausgänge**

| Name | Beschreibung |
|------|--------------|
| CNF  | Signalisiert den Abschluss der Berechnung und die Gültigkeit des Ergebnisses. |

### **Daten-Eingänge**

Es sind keine reinen Dateneingänge vorhanden. Der benötigte Array wird über den **InOut**-Port `A` bereitgestellt.

### **Daten-Ausgänge**

| Name | Typ  | Beschreibung |
|------|------|--------------|
| (leer) | DINT | Resultierende Summe aller Array-Elemente (Typ DINT). |

### **Adapter**

Keine.

## Funktionsweise

Der FB `SUM` akzeptiert ein eindimensionales Array `A` vom Typ `INT` mit beliebiger Länge (deklariert als `ARRAY[*]`). Bei Aktivierung des Ereignisses `REQ` wird der Inhalt des Arrays elementweise aufsummiert. Die Summe wird in einer temporären Variable vom Typ `DINT` akkumuliert, um einen Überlauf zu vermeiden. Nach der vollständigen Iteration über alle gültigen Indizes (von `LOWER_BOUND(A,1)` bis `UPPER_BOUND(A,1)`) wird das Ergebnis an den Ausgang (Datentyp `DINT`) übergeben und das Ereignis `CNF` ausgelöst.

**Wichtiger Hinweis:** Obwohl `A` als **InOut**-Variable deklariert ist, wird ihr Wert während der Berechnung nicht verändert. Sie fungiert in diesem FB ausschließlich als Eingang.

## Technische Besonderheiten

- **Dynamische Array-Größe:** Der FB unterstützt Arrays variabler Länge durch die Verwendung der Funktionen `LOWER_BOUND` und `UPPER_BOUND`, wie von IEC 61131‑3 vorgesehen.
- **Typerweiterung:** Die Summe wird in einem `DINT`-Wert (32‑Bit) zurückgegeben, sodass auch größere Summen von `INT`-Werten (16‑Bit) ohne Überlauf abgebildet werden können.
- **Ereignisgesteuerte Ausführung:** Die Berechnung erfolgt nur bei Bedarf, was eine effiziente Ressourcennutzung ermöglicht.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten. Das Verhalten lässt sich wie folgt beschreiben:

1. **Warten:** Kein Ereignis aktiv – Ausgangszustand.
2. **Berechnung:** Eintritt nach Empfang von `REQ`; Summierung des Arrays.
3. **Bestätigung:** Nach Abschluss der Berechnung wird `CNF` gesendet; Rücksprung in den Wartezustand.

## Anwendungsszenarien

- Aufsummieren von Messwerten eines Sensors über einen bestimmten Zeitraum.
- Berechnung von Gesamtsummen in einer Produktionsanlage (z. B. Stückzahlen, Füllmengen).
- Vorverarbeitung von Datenarrays vor einer weiteren logischen oder arithmetischen Verarbeitung.

## Vergleich mit ähnlichen Bausteinen

- **SUM in IEC 61131‑1:** Der Baustein ist stark an die gleichnamige Funktion aus der IEC 61131‑3 angelehnt, ermöglicht jedoch zusätzlich die ereignisgesteuerte Ausführung und die direkte Einbindung in das 4diac‑Ereignismodell.
- **ADD / MULT:** Während `ADD` oder `MULT` einzelne Zahlenpaare verarbeiten, erlaubt `SUM` die Verarbeitung eines gesamten Arrays in einem Schritt, was die Applikationslogik vereinfacht.

## Fazit

Der Funktionsblock `SUM` bietet eine einfache und performante Möglichkeit, die Summe aller Elemente eines dynamischen Arrays zu berechnen. Durch die ereignisgesteuerte Ausführung und die robuste Handhabung unterschiedlicher Array‑Größen eignet er sich besonders für industrielle Steuerungsaufgaben, bei denen Datenmengen aggregiert werden müssen.