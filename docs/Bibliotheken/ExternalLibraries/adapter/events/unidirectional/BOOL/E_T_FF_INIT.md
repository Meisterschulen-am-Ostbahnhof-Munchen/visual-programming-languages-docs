# E_T_FF_INIT


![E_T_FF_INIT](./E_T_FF_INIT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **E_T_FF_INIT** realisiert ein **Toggle-Flip-Flop** mit integrierter Initialisierungslogik. Er kombiniert das klassische Verhalten eines T‑Flip‑Flops (Umschalten des Ausgangs *Q* bei jedem *CLK*‑Ereignis) mit einer gezielten Setzung des Ausgangs während der Initialisierung. Der Baustein eignet sich besonders für Anwendungen, bei denen nach dem Start ein definierter Anfangszustand erforderlich ist, bevor der normale Toggle‑Betrieb beginnt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Typ    | Mit Variablen | Beschreibung                                          |
|----------|--------|---------------|-------------------------------------------------------|
| **INIT** | EInit  | QI, Q_INIT    | Initialisierungsanforderung; setzt *Q* auf *Q_INIT*.  |
| **CLK**  | Event  | –             | Taktsignal; löst bei jeder steigenden Flanke das Umschalten von *Q* aus (sofern *QI* = TRUE). |

### **Ereignis-Ausgänge**

| Ereignis | Typ    | Mit Variablen | Beschreibung                                         |
|----------|--------|---------------|------------------------------------------------------|
| **INITO**| EInit  | QO            | Initialisierungsbestätigung; signalisiert Ende der Initialisierung. |
| **EO**   | Event  | Q             | Ausgangsereignis; wird nach jeder Zustandsänderung von *Q* ausgegeben. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung                                               |
|----------|-------|------------------------------------------------------------|
| **QI**   | BOOL  | Freigabesignal für die normale Toggle‑Funktion.            |
| **Q_INIT** | BOOL | Gewünschter Wert von *Q* nach der Initialisierung (bei TRUE wird *Q* gesetzt). |

### **Daten-Ausgänge**

| Variable | Typ   | Beschreibung                                               |
|----------|-------|------------------------------------------------------------|
| **QO**   | BOOL  | Ausgangsqualifikator; wird bei INIT auf *QI* gesetzt, bei De‑Initialisierung auf FALSE. |
| **Q**    | BOOL  | Toggle‑Ausgang; wird bei jedem *CLK* umgeschaltet (nur wenn *QI* = TRUE). |

### **Adapter**  
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein arbeitet als **zustandsgesteuerte Maschine (ECC)** mit fünf Zuständen: `START`, `Init`, `DeInit`, `SET` und `RESET`.

1. **Initialisierung (Zustand *Init*)**:  
   - Wird durch das Ereignis **INIT** ausgelöst, sofern *QI* = TRUE.  
   - Der Algorithmus `initialize` setzt *QO* auf den Wert von *QI* (hier TRUE).  
   - Die Transition aus *Init* erfolgt abhängig vom Wert von *Q_INIT*:  
     - *Q_INIT* = TRUE → Wechsel in den Zustand **SET** ( *Q* wird TRUE).  
     - *Q_INIT* = FALSE → Wechsel in den Zustand **RESET** ( *Q* bleibt FALSE).  
   - Nach der Transition wird das Ereignis **INITO** ausgegeben.

2. **De‑Initialisierung (Zustand *DeInit*)**:  
   - Wird durch ein **INIT**-Ereignis mit *QI* = FALSE ausgelöst (aus den Zuständen *SET* oder *RESET*).  
   - Der Algorithmus `deInitialize` setzt *QO* auf FALSE.  
   - Anschließend erfolgt der Übergang zurück in den Startzustand **START** und das Ereignis **INITO** wird ausgegeben.

3. **Normaler Toggle‑Betrieb**:  
   - In den Zuständen **SET** ( *Q* = TRUE) und **RESET** ( *Q* = FALSE).  
   - Bei jedem **CLK**-Ereignis wird zwischen den beiden Zuständen umgeschaltet.  
   - Die Algorithmen `SET` bzw. `RESET` setzen *QO* auf den aktuellen Wert von *QI* und, falls *QI* = TRUE, den Ausgang *Q* auf den entsprechenden Zustand (TRUE oder FALSE).  
   - Nach jedem Wechsel wird das Ereignis **EO** ausgegeben.

**Wichtig**: Die Toggle‑Funktion ist nur aktiv, wenn *QI* = TRUE. Ist *QI* = FALSE, bleibt *Q* unverändert (die IF‑Bedingung in den Algorithmen verhindert die Änderung).

## Technische Besonderheiten
- **Kombinierte Init‑/Toggle‑Logik**: Der Baustein erlaubt es, den Ausgang *Q* bereits während der Initialisierung auf einen definierten Wert zu setzen (*Q_INIT*). Dies unterscheidet ihn von einem einfachen T‑Flip‑Flop, das meist im RESET‑Zustand startet.  
- **Freigabe über QI**: Die Variable *QI* fungiert als globale Freigabe. Nur wenn *QI* = TRUE, erfolgt das Umschalten bei *CLK*. Bei *QI* = FALSE können zwar INIT‑Ereignisse verarbeitet werden, aber der Toggle‑Betrieb ist deaktiviert.  
- **Ausgangsqualifikator QO**: *QO* spiegelt den Freigabezustand wider – er wird bei erfolgreicher Initialisierung auf TRUE, bei De‑Initialisierung auf FALSE gesetzt. Dies ermöglicht eine einfache Überwachung des Baustein‑Status.

## Zustandsübersicht

| Zustand  | Beschreibung                                                           | Eingehende Transition(en)               | Ausgehende Aktion (Algorithmus) | Ausgehendes Ereignis |
|----------|------------------------------------------------------------------------|-----------------------------------------|---------------------------------|----------------------|
| START    | Ruhezustand nach Initialisierung (oder nach De‑Initialisierung).      | *DeInit* → START                        | –                               | –                    |
| Init     | Initialisierungsphase, setzt *QO* und entscheidet über *Q*.           | START → Init (bei INIT & QI = TRUE)    | `initialize`                    | INITO                |
| DeInit   | De‑Initialisierungsphase, setzt *QO* auf FALSE.                       | SET/RESET → DeInit (bei INIT & QI = FALSE) | `deInitialize`                  | INITO                |
| SET      | Normaler Toggle‑Zustand: *Q* = TRUE.                                  | Init → SET (bei Q_INIT = TRUE)<br>RESET → SET (bei CLK) | `SET`                           | EO                   |
| RESET    | Normaler Toggle‑Zustand: *Q* = FALSE.                                 | Init → RESET (bei Q_INIT = FALSE)<br>SET → RESET (bei CLK) | `RESET`                         | EO                   |

**Transitionsbedingungen** (vereinfacht):  
- `START → Init` : `INIT & (QI = TRUE)`  
- `Init → SET`   : `(Q_INIT = TRUE)`  
- `Init → RESET` : `(Q_INIT = FALSE)`  
- `SET ↔ RESET`  : `CLK`  
- `SET / RESET → DeInit` : `INIT & (QI = FALSE)`  
- `DeInit → START` : immer (Bedingung = 1)

## Anwendungsszenarien
1. **Initialisieren einer Maschine mit definiertem Startzustand**  
   Ein Förderband soll nach dem Einschalten immer in der Position „bereit“ ( *Q* = TRUE) sein. Mit *Q_INIT* = TRUE und *QI* = TRUE wird dies erreicht. Danach kann ein Taktgeber über *CLK* das Band zwischen den beiden Zuständen hin‑ und herschalten.

2. **Sicherheitsgesteuerter Toggle**  
   Ein Sicherheitssignal *QI* schaltet den Baustein frei. Nur wenn dieses Signal aktiv ist, dürfen Toggle‑Operationen durchgeführt werden. Ein Ausfall der Freigabe ( *QI* = FALSE) führt zur De‑Initialisierung – der Ausgang *Q* bleibt unverändert und *QO* wird FALSE.

3. **Zustandsablauf mit Initialisierungsblock**  
   In einer Ablaufsteuerung wird *E_T_FF_INIT* als Flip‑Flop für einen Schritt eingesetzt. Die Initialisierung erlaubt es, den Schritt direkt nach dem Start entweder aktiv oder inaktiv zu setzen, ohne einen separaten Setz‑ oder Rücksetzimpuls.

## Vergleich mit ähnlichen Bausteinen

| Baustein        | Besonderheit                                                                 |
|-----------------|------------------------------------------------------------------------------|
| **E_T_FF**      | Reines T‑Flip‑Flop ohne Initialisierungslogik. Startet stets im RESET‑Zustand. |
| **E_FF**        | S‑R‑ oder D‑Flip‑Flop – erlaubt Setzen und Rücksetzen über separate Ereignisse. |
| **E_SR**        | Speicherbaustein (Set‑Reset) ohne Toggle‑Eigenschaft.                        |
| **E_T_FF_INIT** | Kombiniert Toggle mit frei wählbarem Anfangszustand und Freigabe über *QI*.  |

Im Gegensatz zu *E_T_FF* kann *E_T_FF_INIT* den Ausgang bei der Erstinitialisierung auf TRUE setzen und bietet über *QI* eine explizite Freigabe für den Toggle‑Betrieb.

## Fazit
Der Funktionsblock **E_T_FF_INIT** ist eine erweiterte Variante eines T‑Flip‑Flops, die speziell für Steuerungen entwickelt wurde, die nach dem Hochfahren einen definierten Ausgangszustand benötigen. Die Kombination aus Initialisierung (über *Q_INIT*), Freigabe (über *QI*) und Umschaltlogik (über *CLK*) macht ihn vielseitig einsetzbar. Er eignet sich für sicherheitskritische Abläufe, bei denen der Betrieb nur bei aktiver Freigabe erfolgen darf, sowie für Anwendungen, die einen reproduzierbaren Startzustand erfordern. Die klar strukturierte Zustandsmaschine gewährleistet ein deterministisches und vorhersagbares Verhalten.