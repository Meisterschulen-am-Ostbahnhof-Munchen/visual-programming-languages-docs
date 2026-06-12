# AI_D_FF_HYS


![AI_D_FF_HYS](./AI_D_FF_HYS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AI_D_FF_HYS** realisiert ein taktgesteuertes D‑Flipflop (Data Latch) mit einer konfigurierbaren Hysterese. Er dient dazu, ein binäres oder analoges Eingangssignal stabil zu verriegeln und Störungen im Signalverlauf auszufiltern. Die Hysterese verhindert ein ständiges Umschalten bei geringen Signaländerungen (Prellen, Rauschen) und sorgt so für einen sauberen, verzögerungsfreien Ausgangszustand.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Mit Variablen | Beschreibung                |
|----------|-------|---------------|-----------------------------|
| INIT     | EInit | HYSTERESIS    | Initialisierung und Vorgabe des Hysteresebandes |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Beschreibung             |
|----------|-------|--------------------------|
| INITO    | EInit | Bestätigung der Initialisierung |

### **Daten-Eingänge**

| Bezeichnung | Typ  | Beschreibung                           |
|-------------|------|----------------------------------------|
| HYSTERESIS  | INT  | Hysterese-Bandbreite (z. B. in digitalen Schritten) |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Daten-Ausgänge. Der verriegelte Wert wird über den **Adapter‑Plug Q** zur Verfügung gestellt.

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung                                      |
|-------------|-----|----------|---------------------------------------------------|
| I           | AI  | Socket   | Eingangsadapter: Taktsignal (**E1**) und Daten (**D1**) |
| Q           | AI  | Plug     | Ausgangsadapter: latched value (**D1**) und zugehöriges Ereignis (**E1**) |

Der verwendete Adaptertyp `adapter::types::unidirectional::AI` ist ein unidirektionaler Daten- und Ereigniskanal. Über den Socket **I** werden die Werte des Takts (E1) und der Daten (D1) empfangen; über den Plug **Q** wird der latched Wert (D1) zusammen mit einem Bestätigungsereignis (E1) ausgegeben.

## Funktionsweise

1. **Initialisierung**  
   Der Baustein wird durch das Ereignis **INIT** aktiviert. Dabei wird der übergebene Wert **HYSTERESIS** als Hystereseband gespeichert. Nach erfolgreicher Initialisierung wird **INITO** ausgelöst.

2. **Datenverriegelung**  
   Nach der Initialisierung wartet der Baustein auf ein Taktsignal am Adapter **I** (Ereignis **I.E1**). Bei jedem Taktereignis wird der aktuelle Datenwert **I.D1** eingelesen.  
   Der interne Funktionsblock `E_D_FF_ANY_HYS` vergleicht den eingehenden Wert mit dem zuletzt verriegelten Wert unter Berücksichtigung der Hysterese:
   - Überschreitet der neue Wert den alten Wert um mehr als die Hälfte der Hysterese, wird der neue Wert übernommen (gesetzt).
   - Unterschreitet er den alten Wert um mehr als die Hälfte der Hysterese, wird der neue Wert übernommen (rückgesetzt).
   - Bei geringeren Differenzen bleibt der Ausgang unverändert.

   Der so ermittelte latched Wert wird am Adapter **Q** bereitgestellt: **Q.D1** enthält den digitalen Wert, und das Ereignis **Q.E1** signalisiert die Aktualisierung.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation**  
  Der gesamte Daten- und Ereignisaustausch erfolgt über Adapter. Dies ermöglicht eine lose Kopplung zwischen dem Flipflop und den angeschlossenen Komponenten und erleichtert die Wiederverwendung in verschiedenen Kontexten.
- **Hysterese zur Störunterdrückung**  
  Die Hysterese verhindert ein Flip‑Flop‑Verhalten bei Rauschen oder prellenden Signalen. Die Bandbreite wird als Ganzzahl (INT) übergeben und kann zur Laufzeit über **INIT** neu gesetzt werden.
- **Keine direkten Datenausgänge**  
  Der latched Wert ist nur über den Adapter **Q** zugänglich. Dies erzwingt eine strukturierte Signalweiterleitung im Gesamtsystem.
- **Eingebetteter Funktionsblock**  
  Das eigentliche Flipflop mit Hysterese wird durch den internen FB `E_D_FF_ANY_HYS` realisiert, was die Komplexität kapselt und die Wartung erleichtert.

## Zustandsübersicht

Der FB kennt keine expliziten Zustände im Sinne einer Endlichen Automaten. Er befindet sich nach der **INIT**-Behandlung in einem Betriebszustand, in dem er auf Taktereignisse wartet. Ein erneuter **INIT**‑Aufruf setzt die Hysterese neu und initialisiert die interne Logik.

| Zustand              | Beschreibung                                  |
|----------------------|-----------------------------------------------|
| Initialisiert        | Nach erfolgreichem **INIT** bereit zur Verarbeitung |
| Warten auf Takt      | Erwartet ein **I.E1**-Ereignis am Eingangsadapter |
| Datenverarbeitung    | Bei **I.E1**: Hysterese-Vergleich und ggf. Übernahme |

## Anwendungsszenarien

- **Entprellung von Schaltern und Sensoren**  
  Ein mechanischer Kontakt liefert prellende Signale. Die Hysterese unterdrückt kurzzeitige Änderungen und gibt nur stabile Zustände weiter.
- **Rauschunterdrückung bei analogen Signalen**  
  Ein Analog-Digital-Wandler liefert verrauschte Werte. Die Hysterese verhindert ständiges Umschalten zwischen benachbarten Quantisierungsstufen.
- **Zustandsspeicher in Steuerungen**  
  Der Baustein kann als einfaches D‑Flipflop verwendet werden, um einen digitalen Wert taktgesteuert zu übernehmen und bis zum nächsten Takt zu halten.
- **Schnittstelle zwischen asynchronen und synchronen Systemen**  
  Der Adapter erlaubt die Anbindung von Bausteinen mit unterschiedlichen Ereignistakten, indem das Flipflop als Puffer dient.

## Vergleich mit ähnlichen Bausteinen

| Baustein          | Hysterese | Takteingang | Ausgabeart            | Besonderheit                     |
|-------------------|-----------|-------------|-----------------------|----------------------------------|
| **AI_D_FF_HYS**   | Ja        | Ja          | Adapter (AI)          | Flexible Adapter-Kopplung        |
| Standard D‑FF (61499) | Nein    | Ja          | Direkte Datenausgänge | Keine Störunterdrückung          |
| SR‑Flipflop       | Nein      | Nein        | Direkt                | Set/Reset, kein Takt             |
| Schmitt‑Trigger   | Ja        | Nein        | Analoge Schwelle      | Nur Schwellwert, kein Speicher   |

Der AI_D_FF_HYS kombiniert die Eigenschaften eines getakteten D‑Flipflops mit einer einstellbaren Hysterese und bietet durch die Adapter‑Schnittstelle eine plattformunabhängige Integration in IEC‑61499‑Systeme.

## Fazit

Der **AI_D_FF_HYS** ist ein robuster und flexibler Funktionsblock zur taktgesteuerten Signalverriegelung mit Hysterese. Er eignet sich besonders für Anwendungen, bei denen Störungen aus dem Eingangssignal herausgefiltert werden müssen, ohne auf einen einfachen Takt‑Flipflop verzichten zu können. Die adpaterbasierte Schnittstelle fördert modulare, wiederverwendbare Entwürfe und macht den Baustein zu einem wertvollen Element in der Automatisierungstechnik und Signalverarbeitung.