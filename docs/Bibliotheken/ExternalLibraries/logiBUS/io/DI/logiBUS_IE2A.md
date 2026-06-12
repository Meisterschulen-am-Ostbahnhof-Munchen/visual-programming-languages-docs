# logiBUS_IE2A


![logiBUS_IE2A](./logiBUS_IE2A.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `logiBUS_IE2A` ist ein Composite‑Baustein (Composite FB) zur Verarbeitung von Ereignissen an Digitaleingängen des logiBUS‑Systems. Er erweitert die Funktionalität des zugrundeliegenden Bausteins `logiBUS_IE2` um einen dedizierten Adapter‑Ausgang für Ereignismeldungen und ermöglicht die Übergabe von Parametern wie Langdruckzeiten oder Mehrfachklick‑Zählern. Der Baustein dient als standardisierte Schnittstelle zwischen der logiBUS‑Hardware und einer übergeordneten Steuerungslogik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ   | Kommentar                                 |
|-------|-------|-------------------------------------------|
| INIT  | EInit | Service‑Initialisierung                   |
| REQ   | Event | Service‑Anforderung (Service Request)     |

### **Ereignis-Ausgänge**

| Name  | Typ   | Kommentar                         |
|-------|-------|-----------------------------------|
| INITO | EInit | Initialisierungsbestätigung       |

### **Daten-Eingänge**

| Name       | Typ                              | Kommentar                                                             | Initialwert            |
|------------|----------------------------------|-----------------------------------------------------------------------|------------------------|
| QI         | BOOL                             | Ereignis‑Eingangs‑Qualifier                                          | –                      |
| PARAMS     | STRING                           | Service‑Parameter                                                     | –                      |
| Input      | `logiBUS::io::DI::logiBUS_DI_S` | Identifikation des Digitaleingangs (z. B. Input_I1..I8)               | `logiBUS_DI::Invalid`  |
| InputEvent | `logiBUS::io::DI::logiBUS_DI_Events_S` | Identifikation des Ereignisses (Down, Up, Single‑Click, Double‑Click, etc.) | `logiBUS_DI_Events::Invalid` |
| arg        | UINT                             | Ereignisdaten: Langdruckzeit oder Anzahl Mehrfachklicks (abhängig vom Ereignis) | 65535                  |

### **Daten-Ausgänge**

| Name   | Typ    | Kommentar                             |
|--------|--------|---------------------------------------|
| QO     | BOOL   | Ereignis‑Ausgangs‑Qualifier           |
| STATUS | STRING | Servicestatus                         |

### **Adapter**

| Name | Typ                                                 | Beschreibung                                     |
|------|------------------------------------------------------|--------------------------------------------------|
| IN   | `adapter::types::unidirectional::AE`                | Unidirektionaler Adapter‑Ausgang für Ereignisse (E1) |

## Funktionsweise

Der `logiBUS_IE2A` ist ein reiner Strukturbaustein, der die Logik des internen Bausteins `logiBUS_IE2` kapselt.  
- Beim Eintreffen eines **INIT**‑Ereignisses werden die Daten‑Eingänge `QI`, `PARAMS`, `Input`, `InputEvent` und `arg` an den internen FB weitergeleitet und dort die Initialisierung durchgeführt. Nach erfolgreicher Verarbeitung wird über den Ausgang **INITO** eine Bestätigung mit den Ausgangsdaten `QO` und `STATUS` zurückgegeben.  
- Ein **REQ**‑Ereignis löst eine erneute Anforderung (z. B. erneute Messung) aus, ohne die Parameter erneut zu setzen.  
- Die eigentlichen Ereignismeldungen des Digitaleingangs werden vom internen FB über dessen Ausgänge `IND` und `CNF` auf den Adapter‑Ausgang **IN.E1** gelegt. Dadurch kann die übergeordnete Applikation auf eingehende Ereignisse reagieren, ohne die internen Details des Bausteins kennen zu müssen.

Die Datenflüsse sind im internen Netzwerk fest verdrahtet und entsprechen dem Protokoll des `logiBUS_IE2`.

## Technische Besonderheiten

- **Composite‑Struktur**: Der Baustein enthält keine eigene Zustandsmaschine, sondern delegiert die gesamte Logik an den internen FB `logiBUS_IE2`.  
- **Vordefinierte Initialwerte**: Die Eingänge `Input` und `InputEvent` sind auf `Invalid` vorbesetzt, `arg` auf `65535`. Dadurch werden Fehlkonfigurationen vermieden, solange die Parameter nicht explizit gesetzt werden.  
- **Adapter‑Ausgang**: Die Ereignisausgabe erfolgt über einen unidirektionalen Adapter (`AE`), der eine lose Kopplung an die aufrufende Applikation ermöglicht.  
- **Typ‑Importe**: Der Baustein nutzt spezifische Typdefinitionen aus den Paketen `logiBUS::io::DI` und `logiBUS::io::DI::logiBUS_DI_Events`, was eine konsistente Nutzung im logiBUS‑Ökosystem sicherstellt.

## Zustandsübersicht

Der `logiBUS_IE2A` besitzt keine eigene Zustandsmaschine (kein ECC). Der interne FB `logiBUS_IE2` implementiert die notwendigen Zustände zur Ereigniserkennung und -ausgabe. Aus Sicht des Composite‑Bausteins sind nur die zyklischen Abläufe INIT → INITO sowie REQ → (Ereignisausgabe über Adapter) relevant.

## Anwendungsszenarien

- **Taster‑ und Schalterauswertung**: Erkennung von einfachen und mehrfachen Klicks sowie langen Druckvorgängen an digitalen Eingängen eines logiBUS‑Moduls.  
- **Parametrierbare Ereigniserkennung**: Durch den `arg`‑Eingang können Schwellwerte für Langdruckzeiten oder die Anzahl von Mehrfachklicks dynamisch vorgegeben werden.  
- **Integration in übergeordnete Steuerungen**: Der Adapter‑Ausgang erlaubt eine saubere Anbindung an Automatisierungssysteme, die über Adapter‑Schnittstellen kommunizieren.

## Vergleich mit ähnlichen Bausteinen

- **`logiBUS_IE2`**: Dieser Baustein wird im Inneren des `logiBUS_IE2A` verwendet. Er bietet dieselbe Funktionalität, jedoch ohne den dedizierten Adapter‑Ausgang und ohne die Zusammenfassung der Parameter in einer Composite‑Struktur.  
- **`logiBUS_IE2S`** (falls vorhanden): Ein weiterer Baustein derselben Familie, der sich möglicherweise durch zusätzliche Statusausgaben oder andere Ereignisauswahl unterscheidet.  
- Der **`logiBUS_IE2A`** zeichnet sich durch seine einfache Konfiguration und die standardisierte Adapter‑Schnittstelle aus, die eine Wiederverwendung in unterschiedlichen Projekten erleichtert.

## Fazit

Der `logiBUS_IE2A` ist ein fertig konfektionierter Composite‑Baustein für die ereignisbasierte Verarbeitung von logiBUS‑Digitaleingängen. Er kombiniert die bewährte Logik des `logiBUS_IE2` mit einem Adapter‑Ausgang und parametrierbaren Ereignisdaten. Durch die klare Schnittstelle und die vorgegebenen Initialwerte eignet er sich besonders für modulare und standardisierte Automatisierungslösungen, bei denen eine schnelle Integration und einfache Handhabung im Vordergrund stehen.