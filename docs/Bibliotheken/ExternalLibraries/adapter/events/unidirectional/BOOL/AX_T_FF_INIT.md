# AX_T_FF_INIT


![AX_T_FF_INIT](./AX_T_FF_INIT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_T_FF_INIT** realisiert ein getriggertes Toggle-Flipflop mit Initialisierungsfunktion. Er kann über ein INIT-Ereignis in einen definierten Startzustand versetzt werden und wechselt anschließend bei jedem CLK-Ereignis zwischen den Zuständen SET und RESET. Der aktuelle Zustand wird über einen Adapterausgang bereitgestellt. Der Baustein ist besonders geeignet für Anwendungen, bei denen ein Ausgangssignal bei jedem Takt umgeschaltet werden soll, wobei der Anfangszustand über eine Initialisierung festgelegt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| INIT | EInit | Initialisierungsanforderung; triggert die Initialisierung des Flipflops. Die zugehörigen Daten-Eingänge QI und Q_INIT werden ausgewertet. |
| CLK | Event | Takteingang; bei jedem Ereignis wechselt der interne Zustand zwischen SET und RESET. |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| INITO | EInit | Initialisierungsbestätigung; wird nach erfolgreicher Initialisierung oder Deinitialisierung ausgegeben. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| QI | BOOL | Eingangsqualifizierer; steuert, ob Aktionen tatsächlich ausgeführt werden (TRUE = aktiv). |
| Q_INIT | BOOL | Wert, der dem Flipflop bei der Initialisierung zugewiesen wird (TRUE = SET, FALSE = RESET). |

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| QO | BOOL | Ausgangsqualifizierer; spiegelt den Wert von QI wider, wenn eine Aktion ausgeführt wurde, sonst FALSE. |

### **Adapter**

| Name | Typ | Kommentar |
|------|-----|-----------|
| Q | Adapter `adapter::types::unidirectional::AX` | Adapterausgang, der den aktuellen Flipflop-Zustand (TRUE oder FALSE) an verbundene Bausteine weitergibt. |

## Funktionsweise

Der FB besitzt folgende interne Zustände: START, Init, DeInit, SET und RESET.

1. **Initialisierung (INIT-Ereignis)**  
   - Bei einem INIT-Ereignis mit **QI = TRUE** wird vom Startzustand in den Zustand **Init** gewechselt.  
   - Im Zustand Init wird der Algorithmus *initialize* ausgeführt: `QO := QI`.  
   - Anschließend wird der Ausgangsqualifizierer QO auf TRUE gesetzt und das Ereignis **INITO** ausgegeben.  
   - Abhängig vom Wert von **Q_INIT** erfolgt der Übergang:  
     - Ist Q_INIT = TRUE → Wechsel in den Zustand **SET**  
     - Ist Q_INIT = FALSE → Wechsel in den Zustand **RESET**  

2. **Toggle-Betrieb (CLK-Ereignis)**  
   - Ausgehend von **SET** oder **RESET** wechselt bei jedem **CLK**-Ereignis der Zustand:  
     - Von SET → RESET (und umgekehrt)  
   - Beim Verlassen der Zustände werden die entsprechenden Algorithmen ausgeführt:  
     - **SET**: `QO := QI;` Wenn QI = TRUE, wird dem Adapterausgang **Q.D1 = TRUE** zugewiesen.  
     - **RESET**: `QO := QI;` Wenn QI = TRUE, wird dem Adapterausgang **Q.D1 = FALSE** zugewiesen.  
     - In beiden Fällen wird das Ereignis **Q.E1** ausgegeben (über den Adapter).  

3. **Deinitialisierung (INIT-Ereignis mit QI = FALSE)**  
   - Wenn während des Betriebs (in SET oder RESET) ein INIT-Ereignis mit **QI = FALSE** eintrifft, wird in den Zustand **DeInit** gewechselt.  
   - Der Algorithmus *deInitialize* setzt `QO := FALSE`.  
   - Es wird **INITO** ausgegeben, und der FB kehrt in den Startzustand zurück.

Der Baustein bleibt im Startzustand, bis ein INIT mit QI=TRUE eintrifft. Ohne Initialisierung ist kein Toggle-Betrieb möglich.

## Technische Besonderheiten

- **Adapterbasiertes Ausgangssignal**: Der aktuelle Flipflop-Zustand wird nicht als einfacher Datenausgang, sondern über einen **Adapter** (`adapter::types::unidirectional::AX`) bereitgestellt. Dies ermöglicht eine flexible und typisierte Verbindung mit anderen Bausteinen, die denselben Adapter verwenden.  
- **Zustandsabhängige Ausführung**: Die Aktionen (Setzen/Rücksetzen des Adapterausgangs) werden nur dann ausgeführt, wenn der Qualifizierer **QI** = TRUE ist. Ist QI = FALSE, wird der Adapterausgang nicht verändert, der Zustand wechselt jedoch dennoch.  
- **Initialisierung mit Startwert**: Über den Eingang **Q_INIT** kann der Anfangszustand nach der Initialisierung gezielt festgelegt werden (TRUE = gesetzt, FALSE = zurückgesetzt).  

## Zustandsübersicht

| Zustand | Bedeutung |
|---------|-----------|
| START | Warte auf erstes INIT-Ereignis. |
| Init | Initialisierung läuft; QO wird auf QI gesetzt, dann Übergang zu SET oder RESET abhängig von Q_INIT. |
| DeInit | Deinitialisierung läuft; QO wird auf FALSE gesetzt, Rückkehr zu START. |
| SET | Flipflop ist im gesetzten Zustand; Adapterausgang Q.D1 = TRUE (bei QI=TRUE). |
| RESET | Flipflop ist im zurückgesetzten Zustand; Adapterausgang Q.D1 = FALSE (bei QI=TRUE). |

Die Zustandsübergänge werden durch die Ereignisse INIT (mit entsprechender Bedingung an QI) und CLK gesteuert.

## Anwendungsszenarien

- **Steuerung von Ausgängen mit Toggle-Funktion**: Ein digitaler Ausgang soll bei jedem Takt zwischen Ein und Aus wechseln, z. B. für Blinksignale oder Impulsfolgen.  
- **Initialisierbare Zustandsmaschinen**: In Automatisierungssystemen, in denen ein Prozess nach einem Reset einen definierten Startzustand einnehmen muss (gesetzt oder zurückgesetzt).  
- **Adapter-basierte Kommunikation**: Bausteine, die den gleichen Adapter verwenden, können den Flipflop-Zustand direkt auslesen, ohne auf separate Data-Outputs angewiesen zu sein.  

## Vergleich mit ähnlichen Bausteinen

| Kriterium | AX_T_FF_INIT | Einfaches Toggle-FF (ohne INIT) | SR-Flipflop |
|-----------|--------------|------------------------------|-------------|
| Initialisierung | Ja, über INIT mit Q_INIT | Nein, Zustand nach Start undefiniert | Nein (set/reset über separate Eingänge) |
| Zustandswechsel | Gettaktet durch CLK | Gettaktet durch CLK | Asynchron über S und R |
| Ausgang | Über Adapter (typisiert) | Oft als BOOL-Datenausgang | BOOL-Datenausgang |
| Qualifizierer QI | Steuert, ob Aktion ausgeführt wird | Nicht vorhanden | Nicht vorhanden |

Der **AX_T_FF_INIT** bietet im Vergleich zu einem einfachen Toggle-Flipflop die Möglichkeit einer definierten Initialisierung und verwendet einen Adapter für den Ausgang, was in komplexen Systemen die Konfiguration vereinfacht.

## Fazit

Der Funktionsblock **AX_T_FF_INIT** ist ein vielseitiger Baustein für getaktete Toggle-Operationen mit Initialisierungslogik. Seine Kombination aus INIT- und CLK-Ereignissen, dem Qualifizierer QI und dem Adapterausgang erlaubt eine präzise Steuerung des Zustandsverhaltens. Er eignet sich besonders für industrielle Automatisierungsanwendungen, in denen ein definierter Startwert und ein getaktetes Umschalten erforderlich sind.