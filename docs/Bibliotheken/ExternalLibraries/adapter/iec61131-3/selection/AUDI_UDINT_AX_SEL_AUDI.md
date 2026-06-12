# AUDI_UDINT_AX_SEL_AUDI


![AUDI_UDINT_AX_SEL_AUDI](./AUDI_UDINT_AX_SEL_AUDI.svg)

* * * * * * * * * *
## Einleitung

Der Baustein **AUDI_UDINT_AX_SEL_AUDI** realisiert eine binäre Auswahl zwischen zwei Datenquellen. Ein interner IEC 61131-Selektionsbaustein (F_SEL) wählt basierend auf einem booleschen Selektorsignal entweder den Wert von einem Adaptereingang oder einem direkten Dateneingang aus und gibt das Ergebnis über einen Adapterausgang weiter. Der Baustein ist als Composite-Funktionsblock modelliert und nutzt Adapter für eine flexible und typsichere Kopplung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| EI1  | Event | Setzt den Wert von IN1 (wird nicht direkt ausgewertet, dient der Synchronisation der Datenbereitstellung) |

### **Ereignis-Ausgänge**

Der Baustein besitzt **keine eigenen Ereignisausgänge**. Die Ereignissteuerung erfolgt über den Adapterausgang **OUT** (siehe Adapter).

### **Daten-Eingänge**

| Name | Typ   | Kommentar |
|------|-------|-----------|
| IN1  | UDINT | Zweite auswählbare Eingangsvariable (direkt) |

### **Daten-Ausgänge**

Der Baustein hat **keine eigenen Datenausgänge**. Die Ausgabedaten werden über den Adapter **OUT** bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket  | IN0  | adapter::types::unidirectional::AUDI | Erste auswählbare Eingangsgröße |
| Socket  | G    | adapter::types::unidirectional::AX   | Selektor (enthält das boolesche Auswahlsignal und ein Ereignis) |
| Plug    | OUT  | adapter::types::unidirectional::AUDI | Ausgewählter Ausgang (ausgesteuert mit Ereignis und Daten) |

**Adapterdetails (entsprechend ihrer Typdefinition):**

- **AUDI**: Enthält ein Datum (D1) und ein Ereignis (E1).  
- **AX**: Enthält ein Datum (D1) und ein Ereignis (E1).

## Funktionsweise

Der Baustein ist als Composite realisiert und nutzt intern den Funktionsblock **F_SEL** (Typ `iec61131::selection::F_SEL`).

1. Der Socket **G** liefert über sein Ereignis **E1** den Auslöser für die Selektion.
2. Sobald dieses Ereignis eintrifft, wird der interne **F_SEL** über seinen REQ-Eingang aktiviert.
3. **F_SEL** wertet das boolesche Selektorsignal **G.D1** aus:
   - Ist **G.D1 = FALSE**, wird der Wert von **IN0** (über Adapterdaten **IN0.D1**) an den Ausgang **OUT** weitergegeben.
   - Ist **G.D1 = TRUE**, wird der Wert des direkten Dateneingangs **IN1** an den Ausgang **OUT** weitergegeben.
4. Nach erfolgter Auswahl sendet **F_SEL.CNF** ein Ereignis an den Ausgangs-Adapter **OUT.E1**, und der ausgewählte Datenwert wird auf **OUT.D1** gelegt.

Der Ereigniseingang **EI1** dient lediglich der Datenbereitstellung von **IN1** (gemäß WITH-Verknüpfung). Die eigentliche Verarbeitung erfolgt ausschließlich durch das Ereignis des Selektors **G.E1**.

## Technische Besonderheiten

- **Adapterbasierte Schnittstellen**: Statt einzelner Parameter werden komplexe, typisierte Adapter (AUDI, AX) verwendet. Dies ermöglicht eine modulare und wiederverwendbare Kopplung in Hierarchien.
- **Composite-Baustein**: Die innere Logik ist in einem weiteren FB (F_SEL) gekapselt. Die Gesamtfunktion ergibt sich aus der Verschaltung der Subbausteine und Ereignis-/Datenverbindungen.
- **Kein eigener Zustandsautomat**: Der Baustein besitzt keine ECC; die Ablaufsteuerung erfolgt rein über das Ereignisnetz des Composite.

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten. Das Verhalten wird vollständig vom internen F_SEL (IEC 61131-Selektion) abgeleitet, der nach jedem Ereignis auf dem Selektor-Eingang einen neuen Ausgangswert berechnet.

## Anwendungsszenarien

- **Auswahl zwischen zwei Sensorwerten** in landwirtschaftlichen Steuerungen (z. B. zwei unterschiedliche Messquellen für eine Größe).
- **Umschaltung zwischen einem Primär- und einem Backup-Signal**, gesteuert durch einen Fehler- oder Umschaltbefehl.
- **Parametrierbare Konfiguration** von Sollwerten oder Aktorausgängen über einen booleschen Selektor.

## Vergleich mit ähnlichen Bausteinen

- **Einfacher SELECT-FB (IEC 61131-3)**: Realisiert die gleiche Logik ohne Adapter, benötigt separate Eingänge für Selektor, IN0 und IN1.  
  Der vorliegende Baustein kapselt diese Funktionalität in eine adapterorientierte Schnittstelle.
- **MUX-Bausteine (z. B. 4-Kanal-Multiplexer)**: Bieten mehrere Eingänge, hier beschränkt auf zwei Quellen.
- **Ereignisgesteuerte Selektion**: Im Gegensatz zu rein datengetriebenen Selektoren wird die Auswahl nur bei einem Ereignis auf dem Selektor-Kanal durchgeführt.

## Fazit

**AUDI_UDINT_AX_SEL_AUDI** ist ein kompakter, adapterorientierter binärer Selektor. Er eignet sich besonders für Systeme, die auf typsicheren Adapterkopplungen aufbauen, und ermöglicht eine klare Trennung von Ereignis- und Datenflüssen. Durch die Nutzung eines etablierten IEC 61131-Selektionskerns bleibt die Funktion zuverlässig und standardkonform.