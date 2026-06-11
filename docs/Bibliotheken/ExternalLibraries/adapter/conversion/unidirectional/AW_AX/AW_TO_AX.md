# AW_TO_AX


![AW_TO_AX](./AW_TO_AX.svg)

* * * * * * * * * *

## Einleitung

Der Composite-Funktionsblock **AW_TO_AX** dient der Umwandlung eines **AW-Adapters** (WORD) in einen **AX-Adapter** (BOOL). Er prüft, ob der über den AW-Adapter eingehende 16-Bit-Wert ungleich Null ist und gibt das Ergebnis als boolesches Signal über den AX-Adapter aus.

## Schnittstellenstruktur

Der Baustein besitzt keine klassischen Ereignis- oder Datenein-/ausgänge, sondern ausschließlich Adapter-Schnittstellen.

### **Ereignis-Eingänge**

Keine separaten Ereignis-Eingänge. Ereignisse werden über den Socket-Adapter empfangen.

### **Ereignis-Ausgänge**

Keine separaten Ereignis-Ausgänge. Ereignisse werden über den Plug-Adapter gesendet.

### **Daten-Eingänge**

Keine separaten Daten-Eingänge. Daten werden über den Socket-Adapter empfangen.

### **Daten-Ausgänge**

Keine separaten Daten-Ausgänge. Daten werden über den Plug-Adapter gesendet.

### **Adapter**

| Name   | Typ                                    | Richtung | Kommentar                 |
|--------|----------------------------------------|----------|---------------------------|
| AW_IN  | adapter::types::unidirectional::AW     | Socket   | WORD-Adapter-Eingang      |
| AX_OUT | adapter::types::unidirectional::AX     | Plug     | BOOL-Adapter-Ausgang      |

Der Socket **AW_IN** stellt die Ereignis- und Datenschnittstelle eines **WORD**-wertigen Adapters zur Verfügung.  
Der Plug **AX_OUT** stellt die Ereignis- und Datenschnittstelle eines **BOOL**-wertigen Adapters bereit.

## Funktionsweise

Bei Eintreffen eines Ereignisses am **AW_IN.E1** wird der Wert von **AW_IN.D1** mit dem konstanten Wert **WORD#0** verglichen. Dazu wird intern der Baustein **F_NE** (ungleich-Vergleich aus IEC 61131) verwendet.  
- Ist **AW_IN.D1 ≠ 0**, so wird ein Ereignis an **AX_OUT.E1** gesendet und der Datenwert **AX_OUT.D1** auf **TRUE** gesetzt.  
- Andernfalls wird kein Ereignis am Ausgang generiert und der Datenwert bleibt auf **FALSE** (bzw. wird nicht geändert).

Das Verhalten ist ereignisgesteuert und folgt der 61499-Ausführungssemantik: Ein Ereignis am Eingang löst den Vergleich aus, dessen Ergebnis am Ausgang weitergegeben wird.

## Technische Besonderheiten

- Der Baustein ist als **Composite-Funktionsblock** realisiert, d.h. seine Funktionalität wird durch ein inneres Netzwerk aus einem einzelnen **F_NE**-Baustein abgebildet.  
- Er verwendet einen **unidirektionalen Adapter** (AW und AX) gemäß der Adapterdefinition der 4diac-IDE.  
- Die Vergleichslogik stammt aus der IEC 61131-Bibliothek (`iec61131::comparison::F_NE`).  
- Es handelt sich um eine reine Signalumsetzung ohne Zustandsbehaftung.

## Zustandsübersicht

Der Baustein besitzt **keinen internen Zustandsautomaten** (kein ECC). Die Ablaufsteuerung ergibt sich direkt aus dem inneren Netzwerk: Ein Ereignis am Eingangsadapter triggert den Vergleichsbaustein, der wiederum das Ergebnis an den Ausgangsadapter weitergibt.

## Anwendungsszenarien

- **Signalaufbereitung:** Wandlung eines digitalen WORD-Werts (z.B. aus einem Sensor-Modul) in ein boolesches Signal, das anzeigt, ob der Wert von Null verschieden ist.  
- **Adapter-Integration:** Einsatz in Systemen, die eine Adapter-basierte Kommunikation zwischen unterschiedlichen Datentypen erfordern (z.B. Verknüpfung einer WORD-basierten Buskomponente mit einer BOOL-basierten Steuerlogik).  
- **Schwellwertprüfung:** Durch Ändern des Vergleichswerts (im internen Baustein **F_NE**) könnte der Funktionsblock auch auf andere Schwellwerte angepasst werden (z.B. „Wert > 100“).

## Vergleich mit ähnlichen Bausteinen

- **WORD_TO_BOOL:** Einfache direkte Wandlung eines WORD-Datentyps in BOOL (z.B. Bit 0). Der **AW_TO_AX** arbeitet dagegen mit Adaptern und führt einen Vergleich mit Null durch – er reagiert auf das gesamte Word.  
- **Ungleich-Vergleicher (F_NE):** Der **AW_TO_AX** kapselt den **F_NE**-Baustein und fügt die Adapter-Schnittstellen hinzu, sodass er in Adapter-basierten Architekturen verwendet werden kann.

## Fazit

Der **AW_TO_AX** ist ein kompakter, aber nützlicher Composite-Baustein zur Konvertierung von WORD-Adaptern in BOOL-Adapter. Dank seines einfachen Vergleichsprinzips eignet er sich hervorragend für die Integration in ereignisgesteuerte Automatisierungssysteme, die auf Adapter-Schnittstellen basieren. Die klare Trennung von Eingangs- und Ausgangsadaptern erleichtert den modularen Aufbau und die Wiederverwendbarkeit.