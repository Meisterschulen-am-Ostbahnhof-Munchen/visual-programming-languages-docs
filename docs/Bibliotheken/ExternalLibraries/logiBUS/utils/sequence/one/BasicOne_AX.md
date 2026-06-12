# BasicOne_AX


![BasicOne_AX](./BasicOne_AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `BasicOne_AX` ist ein grundlegender IEC 61499-Baustein des Typs *Basic Function Block*, der als Vorlage für einfache Steuerungsaufgaben dient. Er realisiert eine initialisierbare Durchschaltung eines booleschen Signals unter Verwendung unidirektionaler Adapter-Schnittstellen vom Typ `AX`. Der Baustein eignet sich für Szenarien, in denen ein Eingangssignal auf einen Ausgang kopiert und der Initialisierungszustand überwacht werden soll.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Mit Variablen | Kommentar |
|----------|-----|---------------|-----------|
| `INIT` | `EInit` | `QI` | Initialisierungsanforderung |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Mit Variablen | Kommentar |
|----------|-----|---------------|-----------|
| `INITO` | `EInit` | `QO` | Initialisierungsbestätigung |

### **Daten-Eingänge**

| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `QI` | `BOOL` | Eingangsqualifizierer (Schaltet die Initialisierung ein/aus) |

### **Daten-Ausgänge**

| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `QO` | `BOOL` | Ausgangsqualifizierer (Spiegelt den Initialisierungszustand) |

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Plug (Ausgang) | `DO1` | `adapter::types::unidirectional::AX` | Unidirektionaler Adapter zur Datenweitergabe (AX-Schnittstelle) |
| Socket (Eingang) | `DI1` | `adapter::types::unidirectional::AX` | Unidirektionaler Adapter zum Empfang von Daten (AX-Schnittstelle) |

## Funktionsweise

Der Funktionsblock durchläuft einen endlichen Automaten (ECC) mit den Zuständen `START`, `Init`, `Initialized`, `NormalOp` und `DeInit`.

- **START** → **Init**: Wird beim Eintreffen des Ereignisses `INIT` mit `QI = TRUE` durchlaufen. Der Algorithmus `initialize` setzt `QO` auf den Wert von `QI` (also `TRUE`). Der Ausgang `INITO` signalisiert die erfolgreiche Initialisierung.
- **Init** → **Initialized**: Nach der Initialisierung wechselt der Automat sofort in den Zustand `Initialized` (Transition mit Bedingung `1`). Hier verharrt der Baustein, bis entweder ein Ereignis am Socket `DI1.E1` eintrifft oder ein erneutes `INIT` mit `QI = FALSE` die Deinitialisierung auslöst.
- **Initialized** → **NormalOp**: Beim Eintreffen des Adapter-Ereignisses `DI1.E1` wechselt der Baustein in den Zustand `NormalOp`. Der Algorithmus `normalOperation` führt die eigentliche Durchschaltung durch: Sofern `QI = TRUE` ist, wird der Wert des Adapter-Eingangs `DI1.D1` auf den Adapter-Ausgang `DO1.D1` kopiert. Zudem wird `QO` auf den aktuellen Wert von `QI` gesetzt (bleibt so lange `TRUE`, bis `QI` auf `FALSE` gesetzt wird).
- **NormalOp** → **Initialized**: Nach der Ausführung kehrt der Baustein sofort wieder in den Zustand `Initialized` zurück (Transition `1`), bereit für das nächste `DI1.E1`-Ereignis.
- **Initialized** → **DeInit**: Wird das Ereignis `INIT` mit `QI = FALSE` empfangen, erfolgt die Deinitialisierung. Der Algorithmus `deInitialize` setzt `QO` auf `FALSE` und den Adapter-Ausgang `DO1.D1` auf `FALSE`. Anschließend wird `INITO` ausgegeben.
- **DeInit** → **START**: Nach der Deinitialisierung kehrt der Automat in den Startzustand zurück und erwartet eine erneute Initialisierung.

Zusammenfassend arbeitet der Baustein als *getriggerte Durchschaltung*: Der Adapter-Eingang wird bei jedem Ereignis am Socket auf den Adapter-Ausgang kopiert, jedoch nur, wenn der Baustein zuvor korrekt initialisiert wurde (`QI=TRUE` beim `INIT`).

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Die Ein-/Ausgabedaten werden nicht über direkte Variablen, sondern über die unidirektionalen Adapter `DI1` und `DO1` (Typ `AX`) ausgetauscht. Dies ermöglicht flexible Kopplung mit anderen Bausteinen desselben Adaptertyps.
- **Initialisierungslogik**: Der Baustein unterscheidet zwischen initialisiertem (`QI=TRUE`) und deinitialisiertem (`QI=FALSE`) Zustand. Nur nach erfolgreicher Initialisierung werden eingehende Adapter-Ereignisse verarbeitet.
- **Paketname**: Der Baustein ist im Paket `logiBUS::utils::sequence::one` organisiert, was auf eine Verwendung in einer logiBUS-Umgebung hindeutet.
- **Automatische Zustandswechsel**: Die Transitionen von `Init→Initialized`, `NormalOp→Initialized` und `DeInit→START` erfolgen ohne weitere Bedingung (Transition `1`), d.h. die Ausführung der Algorithmen ist jeweils abgeschlossen.

## Zustandsübersicht

Der ECC (Execution Control Chart) des Bausteins umfasst fünf Zustände:

| Zustand | Beschreibung |
|---------|--------------|
| `START` | Wartet auf erstes `INIT`-Ereignis mit `QI=TRUE`. |
| `Init` | Führt Initialisierungsalgorithmus aus, setzt `QO=QI` und sendet `INITO`. |
| `Initialized` | Ruhezustand nach erfolgreicher Initialisierung; wartet auf `DI1.E1` oder erneutes `INIT` (mit `QI=FALSE`). |
| `NormalOp` | Führt Durchschaltung durch (kopiert `DI1.D1` nach `DO1.D1`, falls `QI=TRUE`). |
| `DeInit` | Führt Deinitialisierung durch (setzt `QO` und `DO1.D1` auf `FALSE`), sendet `INITO`. |

## Anwendungsszenarien

- **Signaldurchschaltung mit Sicherung**: Ein boolesches Signal (z.B. Freigabe eines Prozesses) soll nur dann von einer Quelle zu einer Senke weitergegeben werden, wenn der Baustein zuvor initialisiert wurde. Ein erneutes `INIT` mit `QI=FALSE` unterbricht die Durchschaltung.
- **Initialisierungssequenz in Fertigungsanlagen**: Vor dem Start einer Produktion wird der Baustein initialisiert (z.B. Prüfung von Sicherheitsbedingungen). Erst danach dürfen Aktoren über `DO1` angesteuert werden.
- **Datenweitergabe in modularen Systemen**: Der unidirektionale Adapter `AX` erlaubt die lose Kopplung zwischen Modulen – der Baustein dient als einfacher „Durchgang“ in einer Datenkette.

## Vergleich mit ähnlichen Bausteinen

- **BasicOne (ohne Adapter)**: Ein typischer `BasicOne`-Baustein nutzt direkte Ein-/Ausgangsvariablen. `BasicOne_AX` erweitert dies um eine adapterbasierte Schnittstelle, was die Wiederverwendbarkeit und Strukturierung in größeren Systemen verbessert.
- **Standard `E_SR` (Set/Reset)**: Ein Set/Reset-Flipflop speichert einen Zustand, während `BasicOne_AX` keine Speicherfunktion besitzt – der Ausgang folgt dem Eingang nur bei aktiver Initialisierung und bei jedem Ereignis.
- **Move-Funktionsbaustein**: Ein `MOVE`-Baustein kopiert kontinuierlich Werte. `BasicOne_AX` kopiert hingegen nur auf Ereignis (getriggert) und nur nach erfolgter Initialisierung.

## Fazit

Der `BasicOne_AX` ist ein minimalistischer, aber robuster IEC 61499-Baustein für initialisierungsgesteuerte Signaldurchschaltungen mit Adapter-Schnittstelle. Seine klare Zustandslogik und die Trennung von Initialisierung und Betrieb machen ihn besonders geeignet für sicherheitskritische oder sequentielle Anwendungen, in denen ein definierter Startzustand vor der Datenweitergabe erforderlich ist. Die Verwendung unidirektionaler Adapter erhöht die Modularität und erleichtert die Integration in komplexe Automatisierungssysteme.