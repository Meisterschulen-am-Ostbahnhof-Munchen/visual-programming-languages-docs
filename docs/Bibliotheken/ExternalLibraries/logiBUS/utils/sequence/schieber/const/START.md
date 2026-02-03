# START

```{index} single: START
```
## 🎧 Podcast

* [Ereignisse und IEC 61499: Der Startschuss für intelligente Systeme](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Ereignisse-und-IEC-61499-Der-Startschuss-fr-intelligente-Systeme-e368461)

## Einleitung
Die `START`-Konstantendeklaration definiert eine Reihe von ganzzahligen Konstanten (vom Typ `UINT`) für die Verwendung in Steuerungsprogrammen. Diese Konstanten repräsentieren spezifische Zustände, die typischerweise in Sequenzsteuerungen, beispielsweise für Schieber, verwendet werden. Sie dienen der Verbesserung der Code-Lesbarkeit und Wartbarkeit, indem sie numerische Werte durch aussagekräftige Namen ersetzen.

## Schnittstellenstruktur
Bei `START` handelt es sich um eine **GlobalConstants**-Deklaration und nicht um einen Funktionsblock. Daher besitzt sie keine ereignis- oder datenflussbasierten Schnittstellen wie Eingänge oder Ausgänge. Stattdessen definiert sie globale, konstante Werte, die innerhalb anderer Funktionsblöcke oder Programme referenziert werden können.

### **Ereignis-Eingänge**
*Nicht zutreffend.* Diese Deklaration enthält keine Ereigniseingänge.

### **Ereignis-Ausgänge**
*Nicht zutreffend.* Diese Deklaration enthält keine Ereignisausgänge.

### **Daten-Eingänge**
*Nicht zutreffend.* Diese Deklaration enthält keine Dateneingänge.

### **Daten-Ausgänge**
*Nicht zutreffend.* Diese Deklaration enthält keine Datenausgänge.

### **Adapter**
*Nicht zutreffend.* Diese Deklaration verwendet keine Adapter.

## Funktionsweise
Die `START`-Konstantendeklaration weist den symbolischen Namen `STARTClosed`, `STARTOpened` und `STARTUnknown` feste, unveränderliche numerische Werte zu. Sobald diese Deklaration in einem Projekt enthalten ist, können die definierten Namen anstelle der rohen Zahlen (5, 6, 7) im gesamten Anwendungscode verwendet werden. Der Compiler ersetzt bei der Übersetzung jeden Verweis auf z.B. `STARTClosed` durch den Wert `UINT#5`.

## Technische Besonderheiten
*   **Typ:** Alle Konstanten sind vom Typ `UINT` (vorzeichenlose Ganzzahl).
*   **Gültigkeitsbereich:** Die Konstanten sind global definiert (`VAR_GLOBAL CONSTANT`) und innerhalb des deklarierten Pakets (`logiBUS::utils::sequence::schieber::const`) verfügbar.
*   **Unveränderlichkeit:** Als Konstanten (`CONSTANT`) können ihre Werte zur Laufzeit nicht geändert werden.
*   **Paketstruktur:** Die Konstanten sind in einer spezifischen Pakethierarchie organisiert, die auf ihre Anwendungsdomäne (Hilfsfunktionen für Sequenzsteuerungen von Schiebern) hinweist.

## Zustandsübersicht
Die Konstanten selbst repräsentieren abstrakte Zustände:
*   `STARTClosed` (Wert 5): Steht für den Zustand "geschlossen" oder "in Ausgangsposition".
*   `STARTOpened` (Wert 6): Steht für den Zustand "geöffnet" oder "in Endposition".
*   `STARTUnknown` (Wert 7): Steht für einen undefinierten, unbekannten oder Fehlerzustand.

## Anwendungsszenarien
Primär werden diese Konstanten in Zustandsautomaten (State Machines) oder Sequenzer-Funktionsblöcken eingesetzt, um die aktuelle Position oder den Status eines Aktors (wie einen linearen Schieber) eindeutig und lesbar zu kodieren. Beispielsweise könnte ein FB seinen internen Zustand oder einen Ausgangswert auf `STARTOpened` setzen, um anzuzeigen, dass der Schieber vollständig geöffnet ist.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu Funktionsblöcken wie `E_SR` (Flip-Flop) oder `E_CYCLE` (Zyklusgeber) besitzt `START` keinerlei Algorithmus oder Verhaltenslogik. Es ist eine reine Datendeklaration. Ähnliche Konstrukte wären andere `GlobalConstants`- oder `Type`-Deklarationen, die ebenfalls symbolische Namen für Werte bereitstellen (z.B. für Fehlercodes oder Betriebsmodi).

## Fazit
Die `START`-Konstantendeklaration ist ein einfaches, aber wesentliches Werkzeug zur Strukturierung und Professionalisierung von IEC 61499-basierten Steuerungsanwendungen. Durch die Verwendung bedeutungsvoller Namen anstelle von "Magic Numbers" wird der Code deutlich verständlicher, weniger fehleranfällig und einfacher zu warten. Ihre Integration ist besonders in größeren Projekten oder wiederverwendbaren Bibliothekskomponenten zu empfehlen.