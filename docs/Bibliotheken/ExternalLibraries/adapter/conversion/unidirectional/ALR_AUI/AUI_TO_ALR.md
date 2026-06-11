# AUI_TO_ALR


![AUI_TO_ALR](./AUI_TO_ALR.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock AUI_TO_ALR ist ein zusammengesetzter Baustein (Composite), der eine Schnittstellenkonvertierung zwischen einem AUI‑Adapter (Datentyp UINT) und einem ALR‑Adapter (Datentyp LREAL) ermöglicht. Er dient als reine Durchleitung und überträgt sowohl Ereignis‑ als auch Datensignale vom Eingangs‑ zum Ausgangsadapter.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **Ereignis über Socket AUI_IN (E1)** – Ereigniseingang vom AUI‑Adapter.  
  Wird intern direkt mit dem Ereignisausgang des ALR‑Adapters verbunden.

### **Ereignis-Ausgänge**

- **Ereignis über Plug ALR_OUT (E1)** – Ereignisausgang zum ALR‑Adapter.  
  Entspricht dem durchgeleiteten Ereignis vom Socket AUI_IN.

### **Daten-Eingänge**

- **Datenwert über Socket AUI_IN (D1)** – Dateneingang vom AUI‑Adapter (Typ UINT).  
  Wird intern direkt mit dem Datenausgang des ALR‑Adapters verbunden.

### **Daten-Ausgänge**

- **Datenwert über Plug ALR_OUT (D1)** – Datenausgang zum ALR‑Adapter (Typ LREAL).  
  Entspricht dem durchgeleiteten Datenwert vom Socket AUI_IN.

### **Adapter**

- **Socket: AUI_IN** – Quelle (Typ `adapter::types::unidirectional::AUI`)  
  Nimmt die Eingangssignale (Ereignis + UINT‑Daten) entgegen.

- **Plug: ALR_OUT** – Senke (Typ `adapter::types::unidirectional::ALR`)  
  Stellt die Ausgangssignale (Ereignis + LREAL‑Daten) bereit.

## Funktionsweise

Der FB AUI_TO_ALR arbeitet als reine Koppelstelle. Ereignis und Daten werden vom Socket AUI_IN direkt auf den Plug ALR_OUT weitergeleitet. Die eigentliche Konvertierung von UINT nach LREAL wird nicht innerhalb dieses Bausteins durchgeführt, sondern erfolgt implizit durch die verwendeten Adapter‑Typdefinitionen (unidirektionale Protokolle). Somit fungiert der Composite als standardisierte Schnittstelle, um zwei unterschiedliche Adapterprotokolle miteinander zu verbinden.

## Technische Besonderheiten

- **Composite‑Typ:** Der FB besitzt keinen eigenen Execution‑Control‑Chart (ECC), sondern besteht ausschließlich aus einer Netzwerkverbindung zwischen seinen beiden Adaptern.
- **Direkte Durchleitung:** Keine interne Logik, Verzögerungen oder Zustandsänderungen – der FB ist rein passiv.
- **Adapter‑basiert:** Die verwendeten Adapter sind als unidirektionale Schnittstellen definiert, die je ein Ereignis und einen Datenwert transportieren.

## Zustandsübersicht

Der Baustein hat keine eigenen Zustände, da er als Composite ohne ECC realisiert ist. Das Verhalten wird vollständig durch die verbundenen Adapter bestimmt.

## Anwendungsszenarien

- **Protokollanpassung in der Agrartechnik:** Einsatz in Steuerungen, die zwischen verschiedenen Sensor‑ oder Aktorschnittstellen vermitteln müssen.
- **Nachrüstung oder Migration:** Ermöglicht den Einsatz eines ALR‑kompatiblen Geräts an einem bestehenden AUI‑Anschluss, ohne die eigentliche Konvertierung selbst implementieren zu müssen.
- **Modulare Verkabelung:** Als einfaches Verbindungsglied in einer Kette von Adapter‑Bausteinen, z. B. in einer Feldbus‑ oder Kommunikationshierarchie.

## Vergleich mit ähnlichen Bausteinen

Ähnliche Konverterbausteine existieren für andere Adapterpaare (z. B. `AUI_TO_AREAL`, `AUI_TO_BOOL`). Im Gegensatz zu diesen übernimmt AUI_TO_ALR keine aktive Datenumformung, sondern verlässt sich auf die implizite Typwandlung durch die Adapterdefinition. Dies macht ihn besonders leichtgewichtig und geeignet für reine Durchleitungsaufgaben.

## Fazit

Der AUI_TO_ALR ist ein minimaler, aber klar definierter Composite‑FB, der die Verbindung zwischen einem AUI‑ und einem ALR‑Adapter herstellt. Aufgrund seiner Einfachheit und Transparenz eignet er sich hervorragend für die strukturierte Verkabelung in IEC‑61499‑basierten Automatisierungssystemen, insbesondere in Umgebungen, in denen unterschiedliche Adapterprotokolle aufeinander abgestimmt werden müssen.