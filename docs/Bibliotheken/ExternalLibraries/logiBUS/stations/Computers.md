# Computers

```{index} single: Computers
```

* * * * * * * * * *
## Einleitung
Die Globalkonstanten `Computers` stellen eine Sammlung von vordefinierten Netzwerkadressen (IP-Adressen und Ports) als Zeichenketten (`WSTRING`) zur Verfügung. Sie dienen der zentralen Verwaltung von Verbindungsinformationen für verschiedene Rechner oder Stationen innerhalb eines logiBUS-Projekts. Durch die Verwendung dieser Konstanten wird die Wartbarkeit und Lesbarkeit des Codes verbessert, da Änderungen an Netzwerkadressen nur an einer zentralen Stelle vorgenommen werden müssen.

## Schnittstellenstruktur
Bei Globalkonstanten handelt es sich nicht um einen Funktionsbaustein im klassischen Sinne, daher existieren keine Ereignis- oder Datenschnittstellen. Stattdessen werden Konstantendeklarationen bereitgestellt, die projektweit zur Verfügung stehen.

### **Daten-Eingänge**
*Nicht zutreffend.* Konstanten sind feste Werte und besitzen keine Eingänge.

### **Daten-Ausgänge**
*Nicht zutreffend.* Konstanten werden direkt in Ausdrücke oder Zuweisungen eingebunden.

### **Adapter**
*Nicht zutreffend.*

## Funktionsweise
Die Konstanten werden beim Kompilieren des Projekts definiert. Jede Konstante erhält einen festen, unveränderlichen Wert vom Typ `WSTRING` (Wide String). Sobald das Programm läuft, können diese Konstantennamen (`C_LO`, `C_ET`, etc.) anstelle der hartkodierten Zeichenketten in jedem Teil des Programms verwendet werden, das diese Konstanten importiert oder kennt.

## Technische Besonderheiten
*   **Typ:** Alle Konstanten sind vom Typ `WSTRING`, der Unicode-Zeichenketten unterstützt.
*   **Gültigkeitsbereich:** Als globale Konstanten sind sie innerhalb des deklarierten Pakets (`logiBUS::stations`) verfügbar.
*   **Initialisierung:** Die Werte werden direkt bei der Deklaration zugewiesen und sind zur Laufzeit schreibgeschützt.
*   **Verwendung:** Sie sind typischerweise für die Konfiguration von Kommunikationsbausteinen (z.B. `PUBLISH`, `SUBSCRIBE`, `CLIENT`, `SERVER`) vorgesehen, wo die Adresse des Kommunikationspartners benötigt wird.

## Zustandsübersicht
*Nicht zutreffend.* Konstanten haben keinen Zustand.

## Anwendungsszenarien
1.  **Vereinfachte Adresskonfiguration:** In einem verteilten Steuerungssystem mit mehreren Steuerungen (z.B. Hauptsteuerung, Etagensteuerung) können die IP-Adressen der einzelnen Geräte hier zentral hinterlegt werden.
2.  **Portabilität zwischen Umgebungen:** Durch das einfache Austauschen der Werte in dieser Konstantendatei kann ein Programm schnell zwischen verschiedenen Netzwerkumgebungen (z.B. Entwicklungslokalhost, Testnetzwerk, Produktionsnetzwerk) angepasst werden.
3.  **Vermeidung von Tippfehlern:** Die Verwendung des Konstantennamens `C_ET` ist weniger fehleranfällig als das wiederholte Eintippen der Zeichenkette `"192.168.5.1:61499"`.

## Vergleich mit ähnlichen Bausteinen
*   **`VAR_GLOBAL` (Globale Variablen):** Im Gegensatz zu globalen Variablen können Konstanten (`CONSTANT`) nach der Initialisierung nicht mehr verändert werden. Sie bieten somit höhere Programmsicherheit.
*   **`VAR_CONFIG` (Konfigurationsvariablen):** Konfigurationsvariablen sind ebenfalls Konstanten, die jedoch pro Ressource konfiguriert werden können. Die hier definierten globalen Konstanten haben einen festen, projekteinheitlichen Wert.
*   **Direkte Wertangabe:** Der direkte Einsatz von Zeichenketten-Literalen im Code ist möglich, führt aber zu schlechterer Wartbarkeit und höherer Fehleranfälligkeit im Vergleich zur Verwendung zentraler Konstanten.

## Fazit
Die Globalkonstanten `Computers` sind ein einfaches, aber äußerst nützliches Werkzeug zur Strukturierung und Pflege von Netzwerkverbindungsdaten in 4diac-Projekten. Sie fördern saubere Programmierpraktiken, reduzieren Redundanz und machen den Code anpassungsfähiger gegenüber Änderungen in der Netzwerktopologie. Ihre Verwendung wird insbesondere in größeren oder verteilten Automatisierungsanlagen empfohlen.