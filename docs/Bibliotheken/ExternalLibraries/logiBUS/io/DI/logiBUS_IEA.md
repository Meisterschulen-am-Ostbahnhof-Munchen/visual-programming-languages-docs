# logiBUS_IEA


![logiBUS_IEA](./logiBUS_IEA.svg)

* * * * * * * * * *
## Einleitung

Der Composite-Funktionsblock `logiBUS_IEA` dient der ereignisgesteuerten Verarbeitung von digitalen Eingangsdaten in einem logiBUS-Feldbus-System. Er kapselt einen internen `logiBUS_IE`-Baustein und stellt dessen Funktionalität über eine einheitliche Schnittstelle zur Verfügung. Der FB ermöglicht die Initialisierung sowie die Abfrage von Ereignissen an einem digitalen Eingang und gibt die resultierenden Indikationen über einen Adapter an die Ressource weiter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar | Mitgeführte Daten |
|------|-----|-----------|-------------------|
| `INIT` | EInit | Service Initialization | `QI`, `PARAMS`, `Input`, `InputEvent` |
| `REQ` | Event | Service Request | `QI` |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar | Mitgeführte Daten |
|------|-----|-----------|-------------------|
| `INITO` | EInit | Initialization Confirm | `QO`, `STATUS` |

### **Daten-Eingänge**

| Name | Typ | Kommentar | Initialwert |
|------|-----|-----------|-------------|
| `QI` | BOOL | Event Input Qualifier | – |
| `PARAMS` | STRING | Service Parameters | – |
| `Input` | `logiBUS::io::DI::logiBUS_DI_S` | Identifiziert den Eingang (z. B. Input_I1..I8) | `logiBUS_DI::Invalid` |
| `InputEvent` | `logiBUS::io::DI::logiBUS_DI_Events_S` | Identifiziert das Ereignis (z. B. Down, Up, Single-Click, Double-Click) | `logiBUS_DI_Events::Invalid` |

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `QO` | BOOL | Event Output Qualifier |
| `STATUS` | STRING | Service Status |

### **Adapter**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `IN` | `adapter::types::unidirectional::AE` | Indication from Resource |

Der Adapter `IN` nimmt die vom internen Baustein erzeugten Ereignisse (`DI.IND` und `DI.CNF`) entgegen und leitet sie als „Indication“ an die übergeordnete Ressource weiter.

## Funktionsweise

Der FB `logiBUS_IEA` arbeitet als reiner Composite-Bautein, d. h. er besitzt keine eigene Ablaufsteuerung, sondern leitet alle Ereignisse und Daten an den eingebetteten Baustein `logiBUS::io::DI::logiBUS_IE` weiter.

- **INIT-Ereignis**:  
  Über den Ereigniseingang `INIT` wird der interne Baustein initialisiert. Dabei werden die Parameter `QI`, `PARAMS`, `Input` und `InputEvent` übergeben. Nach erfolgreicher Initialisierung quittiert der interne Baustein mit dem Ereignis `INITO`, das an den übergeordneten FB zurückgegeben wird. Die Ausgangsdaten `QO` und `STATUS` werden dabei aktualisiert.

- **REQ-Ereignis**:  
  Mit `REQ` (bei gesetztem `QI`) wird eine Anforderung an den internen Baustein gesendet. Dieser verarbeitet die Konfiguration und löst bei erkannten Ereignissen die entsprechenden Indikationen aus.

- **Indikation über Adapter**:  
  Die vom internen Baustein erzeugten Ereignisse `IND` (Indication) und `CNF` (Confirm) werden auf den Adapterausgang `IN.E1` gelegt. Auf diese Weise kann die umgebende Ressource auf Ereignisse wie Tasterdruck oder Doppelklick reagieren.

## Technische Besonderheiten

- **Composite-Baustein**: Der FB enthält keinen eigenen ECC (Execution Control Chart), sondern delegiert die gesamte Logik an den internen `logiBUS_IE`. Dadurch wird die Wiederverwendung und Testbarkeit erhöht.
- **Generische Parametrierung**: Über den `PARAMS`-Eingang können systemspezifische Parameter als String übergeben werden.
- **Adapterbasierte Ereignisausgabe**: Die Nutzung eines unidirektionalen Adapters (Typ `AE`) ermöglicht eine flexible Kopplung an die Ressource ohne feste Verdrahtung auf Ereignisausgänge.
- **Typisierte Eingabeselektion**: Die Eingänge `Input` und `InputEvent` nutzen spezifische Aufzählungstypen (`logiBUS_DI_S` und `logiBUS_DI_Events_S`), die eine sichere und eindeutige Konfiguration erlauben.

## Zustandsübersicht

Da `logiBUS_IEA` ein reiner Composite-Baustein ist, besitzt er keinen eigenen Zustandsautomaten. Der Zustand wird durch den internen Baustein bestimmt. Typische Zustände des inneren `logiBUS_IE` umfassen:

- **IDLE**: Warten auf INIT oder Konfiguration
- **WAIT**: Warten auf ein erkanntes Ereignis am Eingang
- **ACTIVE**: Ereignis erkannt, Indikation wird gesendet
- **ERROR**: Fehler bei Initialisierung oder Kommunikation

Die Zustandsübergänge werden durch die Ereignisse `IND` und `CNF` sichtbar und über den Adapter nach außen kommuniziert.

## Anwendungsszenarien

- **Ereigniserkennung an digitalen Eingängen**: Taster, Schalter oder Sensoren mit Mehrfachklick-Funktionalität (Single/Double-Click) können über `InputEvent` konfiguriert werden.
- **Steuerung von Maschinenmodi**: Ein Digitaleingang löst bei Betätigung (z. B. Down-Ereignis) einen Moduswechsel aus.
- **Parametrierbare Initialisierung**: Über `PARAMS` können Bus-Parameter oder Filterzeiten an den logiBUS-Controller übergeben werden.
- **Integration in größere Composite-Blöcke**: Der Adapter `IN` erlaubt die Anbindung an einen übergeordneten Steuerungsbaustein (z. B. einen Ressourcen-Manager).

## Vergleich mit ähnlichen Bausteinen

| FB-Typ | Eigenschaft |
|--------|-------------|
| `logiBUS_DI` | Reiner Digitaleingang ohne Ereignisdetektion; einfacher Pegelabruf |
| `logiBUS_IEA` | **Dieser FB:** Ereignisbasierte Eingabe mit Initialisierung und Adapter für Indikation |
| `logiBUS_DI_Events` | Ereignisdetektion auf einem einzelnen Eingang, aber ohne Initialisierungslogik |

Gegenüber dem einfachen Digitaleingang bietet `logiBUS_IEA` eine vollständige Initialisierungsschnittstelle und eine standardisierte Ereignissignalisierung über einen Adapter. Im Vergleich zu einem reinen Ereignisbaustein enthält er zusätzlich die INIT-Funktionalität, die für die Inbetriebnahme eines logiBUS-Teilnehmers erforderlich ist.

## Fazit

Der Composite-Baustein `logiBUS_IEA` kapselt die komplexe Initialisierung und Ereignisverarbeitung eines logiBUS-Eingangsmoduls in einer kompakten, wiederverwendbaren Einheit. Durch die klare Trennung von Initialisierung und Anforderung, die Unterstützung typisierter Eingänge sowie die adapterbasierte Ereignisausgabe eignet er sich besonders für den Einsatz in modularen Automatisierungslösungen, bei denen zuverlässige ereignisgesteuerte Eingabeerfassung gefordert ist.