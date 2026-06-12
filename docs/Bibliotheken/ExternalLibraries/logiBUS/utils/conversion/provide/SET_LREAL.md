# SET_LREAL


![SET_LREAL](./SET_LREAL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **SET_LREAL** dient dazu, einen Wert vom Typ LREAL an eine InOut-Variable zu übergeben. Der Eingangswert wird bei einer steigenden Flanke am REQ-Ereignis in die Zielvariable geschrieben und der Vorgang über das CNF-Ereignis quittiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Mit Variablen | Beschreibung |
|----------|---------------|--------------|
| REQ      | IN, OUT       | Normaler Ausführungsanforderung. Löst das Schreiben des Eingangswertes in die Zielvariable aus. |

### **Ereignis-Ausgänge**

| Ereignis | Mit Variablen | Beschreibung |
|----------|---------------|--------------|
| CNF      | OUT           | Bestätigung der erfolgreichen Ausführung. Die Zielvariable wurde aktualisiert. |

### **Daten-Eingänge**

| Name | Typ   | Initialwert | Beschreibung                    |
|------|-------|-------------|----------------------------------|
| IN   | LREAL | 0.0         | Wert, der in die Zielvariable geschrieben werden soll. |
| OUT  | LREAL | 0.0         | (InOut) Eingangsseite der Zielvariablen. Der aktuelle Wert kann gelesen werden. |

### **Daten-Ausgänge**

| Name | Typ   | Initialwert | Beschreibung                          |
|------|-------|-------------|----------------------------------------|
| OUT  | LREAL | 0.0         | (InOut) Ausgangsseite der Zielvariablen. Nach Ausführung wird hier der Wert von IN ausgegeben. |

### **Adapter**

Keine Adapter vorhanden.

## Funktionsweise
Bei einem Ereignis am Eingang **REQ** wird der Algorithmus ausgeführt, der den Wert der Eingangsvariablen **IN** in die InOut-Variable **OUT** kopiert. Anschließend wird das Ereignis **CNF** gesendet. Der Baustein arbeitet rein kombinatorisch und hat keine interne Zustandshaltung über die Ausführung hinaus.

## Technische Besonderheiten
- Der Baustein verwendet eine InOut-Variable. Diese ermöglicht den direkten Zugriff auf eine externe Variable, ohne dass eine zusätzliche Verbindung zwischen Eingang und Ausgang erforderlich ist.
- Der Typ LREAL entspricht einer Gleitkommazahl doppelter Genauigkeit gemäß IEC 61499.
- Der Algorithmus ist in Structured Text (ST) realisiert und sehr einfach gehalten (`OUT := IN;`).

## Zustandsübersicht
Der Baustein besteht aus einem einzigen Zustand **REQ**:
- **REQ**: Wartet auf das Eintreffen des REQ-Ereignisses. Führt dann den Algorithmus aus und sendet CNF. Nach dem Senden kehrt er wieder in den Zustand REQ zurück (implizit, da keine weiteren Zustände definiert sind).

Es gibt keine Verzweigungen oder Zeitsteuerungen.

## Anwendungsszenarien
- **Kopieren eines LREAL-Wertes** in eine globale oder instanzübergreifende Variable, wenn eine direkte Verbindung nicht möglich oder gewünscht ist.
- **Setzen eines Sollwertes** in einer Steuerung, z. B. für einen PID-Regler, bei dem der Wert über einen analogen Eingang kommt.
- **Initialisierung** von Variablen im laufenden Betrieb, ohne die gesamte Applikation neu starten zu müssen.

## Vergleich mit ähnlichen Bausteinen
- **SET_INT** oder **SET_BOOL**: Funktionsgleiche Bausteine für andere Datentypen.
- **MOVE**: Ein allgemeiner MOVE-Baustein (z. B. in IEC 61131-3) kopiert Werte ohne Ereignissteuerung. SET_LREAL hingegen nutzt ereignisgesteuerte Ausführung und InOut-Variablen.
- **WRITE_LREAL**: Manche Bibliotheken bieten separate Bausteine zum Schreiben auf eine Adresse. SET_LREAL ist einfacher und arbeitet auf Variablenebene.

## Fazit
Der **SET_LREAL**-Baustein ist ein einfaches, aber nützliches Werkzeug, um einen LREAL-Wert in eine InOut-Variable zu schreiben. Seine ereignisgesteuerte Arbeitsweise macht ihn leicht in IEC 61499-Applikationen integrierbar. Die klare Schnittstelle mit nur einem Ereignisein- und -ausgang sowie einem Dateneingang und einer InOut-Variable reduziert die Komplexität und erleichtert die Wiederverwendung.