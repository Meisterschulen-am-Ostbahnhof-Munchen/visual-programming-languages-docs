# ISO_NETEVENT_e

```{index} single: ISO_NETEVENT_e
```

* * * * * * * * * *
## Einleitung
Die globale Konstantendatei `ISO_NETEVENT_e` definiert eine Aufzählung (Enumeration) von Ereignistypen für das Netzwerkmanagement in einem ISOBUS-kompatiblen System. Sie stellt benannte, ganzzahlige Konstanten zur Verfügung, die verschiedene Zustandsänderungen und Ereignisse im Netzwerk repräsentieren, wie z.B. das Hinzufügen oder Entfernen von Teilnehmern oder Adresskonflikte. Die Verwendung dieser Konstanten erhöht die Lesbarkeit und Wartbarkeit des Quellcodes.

## Schnittstellenstruktur
Bei `ISO_NETEVENT_e` handelt es sich um eine **Globale Konstantendatei** und nicht um einen Funktionsblock. Daher besitzt sie keine Ereignis- oder Datenschnittstellen im herkömmlichen Sinne. Stattdessen stellt sie eine Sammlung von Konstanten (`VAR_GLOBAL CONSTANT`) zur Verfügung, die systemweit genutzt werden können.

### **Daten-Eingänge**
*Nicht zutreffend.* Diese Ressource definiert Konstanten, keine Eingänge.

### **Daten-Ausgänge**
*Nicht zutreffend.* Diese Ressource definiert Konstanten, keine Ausgänge.

### **Ereignis-Eingänge**
*Nicht zutreffend.*

### **Ereignis-Ausgänge**
*Nicht zutreffend.*

### **Adapter**
*Nicht zutreffend.*

## Funktionsweise
Die Datei deklariert eine Reihe von Konstanten vom Typ `USINT` (Unsigned Short Integer, 8-Bit). Jeder Konstante ist ein eindeutiger numerischer Wert und ein sprechender Name zugeordnet. Diese Konstanten können in anderen Funktionsblöcken oder Programmen importiert und verwendet werden, um Netzwerkereignisse zu identifizieren oder Zustände abzufragen, anstatt magische Zahlen im Code zu verwenden.

## Technische Besonderheiten
*   **Typ:** Alle Konstanten sind vom Typ `USINT`.
*   **Initialisierung:** Jede Konstante wird bei der Deklaration mit einem eindeutigen Wert initialisiert (0 bis 9).
*   **Bedingte Kompilierung:** Die Konstanten `Isonet_HsiActive` und `Isonet_HsiInactive` sind als bedingte Konstanten gekennzeichnet (ursprünglich aus C-Code). Ihre Verwendung kann von der Definition eines Präprozessor-Symbols (`CCI_HSI`) abhängen.
*   **Paketzuordnung:** Die Konstanten sind dem Paket `isobus::pgn` zugeordnet, was auf ihre Verwendung im Kontext der ISOBUS-Protokollbehandlung (Parameter Group Number) hindeutet.

## Zustandsübersicht
*Nicht zutreffend.* Konstanten haben keinen Zustand.

## Anwendungsszenarien
Diese Konstanten werden typischerweise in Funktionsblöcken verwendet, die:
1.  Das ISOBUS-Netzwerkmanagement (Address Claiming, Network Management) implementieren.
2.  Netzwerkereignisse überwachen und auf diese reagieren (z.B. bei Adresskonflikten).
3.  Den Zustand anderer Netzwerkteilnehmer (Controller Applications, ECUs) verwalten.
4.  Diagnose- oder Logging-Funktionen bereitstellen, die Netzwerkereignisse protokollieren.

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken (FB) oder Basis-Funktionsblöcken (BFB) enthält eine Globale Konstantendatei keine ausführbare Logik oder Algorithmen. Sie ist vergleichbar mit einer Header-Datei in C/C++ oder einem `ENUM` in höheren Programmiersprachen. Ihr Zweck ist ausschließlich die Definition von unveränderlichen Werten für die gesamte Anwendung.

## Fazit
Die `ISO_NETEVENT_e` ist eine essentielle Ressource für die strukturierte Entwicklung von ISOBUS-Anwendungen in der 4diac IDE. Sie standardisiert die Kodierung von Netzwerkmanagement-Ereignissen, fördert die Code-Klarheit und reduziert Fehler, die durch die Verwendung undifferenzierter numerischer Werte entstehen können. Ihre Integration ist besonders für komplexe, netzwerkbasierte Steuerungssysteme im landwirtschaftlichen und mobilen Maschinenbereich von Vorteil.