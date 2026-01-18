# sequence

```{index} single: sequence
```

* * * * * * * * * *
## Einleitung
Die globale Konstantendatei `sequence` definiert eine Reihe von vordefinierten Konstanten, die in Verbindung mit Sequenz-Funktionsblöcken verwendet werden können. Sie stellt symbolische Namen für Zustände und einen speziellen Zeitwert bereit, um die Lesbarkeit und Wartbarkeit von IEC 61499-Applikationen zu erhöhen. Die Konstanten sind im Paket `logiBUS::utils::sequence::const` organisiert.

## Schnittstellenstruktur
Globale Konstanten besitzen keine Ereignis- oder Datenschnittstellen im herkömmlichen Sinne eines Funktionsblocks. Stattdessen werden sie als benannte Werte im gesamten Projekt zur Verfügung gestellt. Ihre Struktur ist eine Sammlung von Variablendeklarationen mit festen Initialwerten.

### **Daten-Eingänge**
*Nicht zutreffend.* Globale Konstanten sind keine Eingänge, sondern fest definierte Werte.

### **Daten-Ausgänge**
*Nicht zutreffend.* Globale Konstanten sind keine Ausgänge, sondern fest definierte Werte.

### **Adapter**
*Nicht zutreffend.*

## Funktionsweise
Die Datei definiert Konstanten, die zur Kompilierzeit durch ihre Werte ersetzt werden. Sie können in jedem Funktionsblock innerhalb des Projekts referenziert werden, sofern der entsprechende Namensraum (`logiBUS::utils::sequence::const`) importiert oder der vollqualifizierte Name verwendet wird. Die Verwendung dieser Konstanten anstelle von direkten numerischen Werten ("Magic Numbers") im Code macht die Logik klarer und änderungsresistenter.

## Technische Besonderheiten
*   **Datentypen:** Die Konstanten verwenden die elementaren IEC 61131-3-Datentypen `TIME` und `SINT` (Short Integer).
*   **Besonderer Wert `NO_TIME`:** Die Konstante `NO_TIME` ist mit dem sehr großen Wert `TIME#49d17h2m47s295ms` initialisiert. Dieser Wert dient typischerweise als Platzhalter oder Initialwert, um einen "undefinierten" oder "nicht gesetzten" Zeitpunkt zu kennzeichnen, da er weit außerhalb des Bereichs normaler Steuerungszeiten liegt.
*   **Zustandskonstanten:** Die Konstanten `State_00` bis `State_08` repräsentieren ganzzahlige Zustände (0-8) und sind vom Typ `SINT`. Sie sind für die Verwendung in Zustandsautomaten oder Schrittketten vorgesehen.

## Zustandsübersicht
*Nicht zutreffend.* Dies ist eine Konstantensammlung und enthält keinen Zustandsautomaten.

## Anwendungsszenarien
1.  **Zustandsautomaten / Sequenzer:** Die `State_XX`-Konstanten können als Rückgabewerte oder für Vergleiche in Schrittketten-Funktionsblöcken (z.B. `E_SR`, `E_CTU` in Verbindung mit Logik) verwendet werden, um den aktuellen Schritt lesbar zu identifizieren.
2.  **Zeitgeber-Initialisierung:** Die Konstante `NO_TIME` kann verwendet werden, um Zeitgeber-Funktionsblöcken einen initialen "ungültigen" Wert zuzuweisen, bevor eine echte Zeitdauer gesetzt wird.
3.  **Code-Verständlichkeit:** Ersetzen von Zahlen wie `SINT#5` im Code durch `State_05` verbessert die Lesbarkeit und zeigt die semantische Bedeutung des Wertes an.

## Vergleich mit ähnlichen Bausteinen
*   **ENUM-Datentyp:** Ein benutzerdefinierter Aufzählungstyp (ENUM) könnte eine ähnliche Rolle wie die `State_XX`-Konstanten übernehmen und bietet oft eine strengere Typprüfung. Globale Konstanten sind jedoch einfacher zu definieren und in 4diac zu verwenden.
*   **Direkte Werteingabe:** Der Hauptvorteil gegenüber der direkten Eingabe von Werten (z.B. `3`) ist die zentrale Definition. Eine Änderung des Wertes muss nur an einer Stelle (hier in der Konstantendatei) vorgenommen werden und wirkt sich auf alle Verwendungen aus.

## Fazit
Die globale Konstantendatei `sequence` ist ein nützliches Hilfsmittel zur Strukturierung von Steuerungsanwendungen. Durch die Bereitstellung von sprechenden Namen für Zustände und einen speziellen Zeitwert trägt sie wesentlich zur Erzeugung von klarem, wartbarem und robustem Code bei. Ihre Verwendung wird insbesondere bei der Implementierung von Schrittketten und zustandsbasierten Steuerungen empfohlen.
