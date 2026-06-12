# ASR_SPLIT_9


![ASR_SPLIT_9](./ASR_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **ASR_SPLIT_9** dient dazu, einen einzelnen eingehenden ASR-Adapter (Application Specific Resource) auf neun separate ASR-Ausgänge aufzuteilen. Er ist als generischer Baustein (Generic FB) implementiert und ermöglicht die Verteilung eines ASR-Signals an bis zu neun unabhängige Empfänger.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine vorhanden.

### **Ereignis-Ausgänge**
Keine vorhanden.

### **Daten-Eingänge**
Keine separaten Dateneingänge. Der gesamte Datenaustausch erfolgt über den ASR-Adapter **IN**.

### **Daten-Ausgänge**
Keine separaten Datenausgänge. Die Daten werden über die ASR-Adapter **OUT1** bis **OUT9** ausgegeben.

### **Adapter**

**Socket (Eingang):**
| Name | Typ | Richtung |
|------|-----|----------|
| IN   | `adapter::types::unidirectional::ASR` | Socket |

**Plugs (Ausgänge):**
| Name  | Typ | Richtung |
|-------|-----|----------|
| OUT1  | `adapter::types::unidirectional::ASR` | Plug |
| OUT2  | `adapter::types::unidirectional::ASR` | Plug |
| OUT3  | `adapter::types::unidirectional::ASR` | Plug |
| OUT4  | `adapter::types::unidirectional::ASR` | Plug |
| OUT5  | `adapter::types::unidirectional::ASR` | Plug |
| OUT6  | `adapter::types::unidirectional::ASR` | Plug |
| OUT7  | `adapter::types::unidirectional::ASR` | Plug |
| OUT8  | `adapter::types::unidirectional::ASR` | Plug |
| OUT9  | `adapter::types::unidirectional::ASR` | Plug |

## Funktionsweise

Der Baustein empfängt über den Socket-Adapater **IN** ein ASR-Signal. Dieses Signal wird intern an alle neun Ausgangs-Adapter (**OUT1** bis **OUT9**) weitergeleitet. Somit liegt an jedem Ausgang das identische ASR-Signal an. Eine Verzögerung oder Pufferung findet nicht statt. Der Baustein ist rein passiv und führt keine Transformation der Daten durch.

## Technische Besonderheiten

- **Generischer Baustein:** Der Typ ist als generischer FB (GenericClassName `'GEN_ASR_SPLIT'`) ausgelegt, sodass er je nach Projektkontext mit unterschiedlichen ASR-Typen parametrisiert werden kann.
- **Unidirektionale Adapter:** Alle verwendeten Adapter sind vom Typ `unidirectional::ASR`, was eine klare Datenflussrichtung vom Eingang zu den Ausgängen vorgibt.
- **Keine Ereignisse:** Der Baustein besitzt keine Ereignis-Eingänge oder -Ausgänge. Die Datenweitergabe erfolgt rein über die Adapter-Schnittstellen.
- **Plattformneutral:** Durch die Verwendung des IEC 61499-2 Standards ist der Baustein in verschiedenen 4diac-IDE Projekten einsetzbar.

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten (ECC). Er arbeitet statisch und gibt das eingehende Signal ohne zeitliche oder logische Abhängigkeiten an alle Ausgänge weiter.

## Anwendungsszenarien

- **Verteilung eines ASR-Signals** an mehrere parallel arbeitende Ressourcen oder Funktionseinheiten.
- **Monitoring oder Parallelsteuerung**, wenn mehrere Komponenten dieselben ASR-Daten benötigen (z. B. ein Sensorwert an mehrere Auswertebausteine).
- **Einfache Bus-ähnliche Strukturen** in automatisierten Steuerungen, ohne aufwendige Multicast-Mechanismen.

## Vergleich mit ähnlichen Bausteinen

- **ASR_SPLIT_4 / ASR_SPLIT_2:** Bausteine mit geringerer Ausgangsanzahl (4 bzw. 2). `ASR_SPLIT_9` bietet die maximale Aufteilung auf neun Kanäle.
- **ASR_MERGE:** Führt mehrere ASR-Signale zu einem zusammen, während `ASR_SPLIT_9` genau die umgekehrte Funktion erfüllt.
- **Data Distributor:** Bei Datentyp-orientierten Bausteinen (z. B. `DATA_SPLIT`) wird eher mit einfachen Datentypen gearbeitet. `ASR_SPLIT_9` ist speziell für komplexe Adapterstrukturen optimiert.

## Fazit

Der Funktionsbaustein **ASR_SPLIT_9** ist eine kompakte und effiziente Lösung zur Verteilung eines ASR-Signals auf neun identische Ausgänge. Durch den generischen Charakter und die klare, ereignislose Adapterkopplung eignet er sich besonders für modulare, wiederverwendbare Automatisierungssysteme auf Basis von IEC 61499.