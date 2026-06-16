# AW_MUX_3


![AW_MUX_3](./AW_MUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `AW_MUX_3` ist ein generischer Multiplexer (MUX) mit drei Eingängen. Er wählt anhand eines Index-Parameters einen der drei Adapter-Eingänge aus und leitet dessen Werte an den Ausgang weiter. Der Baustein dient zur dynamischen Umschaltung zwischen verschiedenen Datenquellen in industriellen Steuerungsanwendungen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Setzt den Index K und löst die Umschaltung aus. |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigung der erfolgten Umschaltung auf den durch K spezifizierten Eingang. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `K` | UINT | Index des auszuwählenden Eingangs (0, 1 oder 2). |

### **Daten-Ausgänge**
Keine direkten Datenausgänge vorhanden. Die Ausgabe erfolgt über den Adapter `OUT`.

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| `IN1` | `AW` (unidirectional) | Socket | Eingangswert 1 (ausgewählt bei K = 0). |
| `IN2` | `AW` (unidirectional) | Socket | Eingangswert 2 (ausgewählt bei K = 1). |
| `IN3` | `AW` (unidirectional) | Socket | Eingangswert 3 (ausgewählt bei K = 2). |
| `OUT` | `AW` (unidirectional) | Plug | Ausgangswert – verbindet die interne Logik mit dem ausgewählten Eingang. |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert:
- Ein Ereignis an `REQ` liest den aktuellen Wert des Daten-Eingangs `K` (Typ UINT).
- Abhängig vom Wert `K` wird der entsprechende Socket-Eingang (`IN1`, `IN2`, `IN3`) auf den Plug `OUT` durchgeschaltet.
- Nach erfolgreicher Umschaltung wird ein Ereignis an `CNF` gesendet.

Gültige Werte für `K` sind 0, 1 und 2. Werte außerhalb dieses Bereichs führen zu undefiniertem Verhalten; der Baustein kann dann keinen gültigen Eingang auswählen.

## Technische Besonderheiten
- **Generischer Typ**: Der Baustein ist als generischer FB (`GEN_AW_MUX`) deklariert. Die tatsächliche Implementierung kann für verschiedene Datenformate des Adapters `AW` parametrisiert werden.
- **Adapter-basiert**: Die Ein- und Ausgänge nutzen den Adaptertyp `adapter::types::unidirectional::AW`, der unidirektionale Datenflüsse (z. B. analoge Messwerte oder einfache Strukturen) unterstützt.
- **Ereignisgesteuerte Verarbeitung**: Keine zyklische Aktualisierung – die Umschaltung erfolgt nur bei Anforderung über `REQ`.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine in der XML-Definition. Sein Verhalten entspricht einem einfachen, ereignisgesteuerten Selektionsmechanismus:
- **IDLE**: Warten auf ein `REQ`-Ereignis.
- **SELECT**: Auswertung von `K` und Verbindung des entsprechenden Eingangs mit dem Ausgang.
- **CONFIRM**: Senden von `CNF` und Rückkehr in den IDLE-Zustand.

## Anwendungsszenarien
- **Umschalten zwischen mehreren Sensoren**: Auswahl eines von drei analogen Messfühlern (z. B. Temperatur, Druck) zur Weiterverarbeitung.
- **Routing von Steuersignalen**: Wahl zwischen verschiedenen Regelungsalgorithmen oder Quellen für ein Stellsignal.
- **Multiplexen in Visualisierungen**: Bei Bedarf können über den Index unterschiedliche Anzeigewerte an ein Anzeigegerät geschaltet werden.

## Vergleich mit ähnlichen Bausteinen
- **AW_MUX_2**: Zwei Eingänge, Indexbereich 0…1. `AW_MUX_3` bietet einen zusätzlichen dritten Eingang.
- **Standard-MUX (z. B. E_MUX)**: Nutzt oft einfache Datentypen (INT, REAL) statt Adapter. Der Adapter-basierte Ansatz erlaubt komplexere Datenstrukturen und eine lose Kopplung zwischen Komponenten.
- **AW_SELECT** (hypothetisch): Kann einen von mehreren Adaptereingängen selektieren, jedoch ohne Indexsteuerung (z. B. über Boolesche Auswahl). `AW_MUX_3` erlaubt eine numerische, erweiterbare Selektion.

## Fazit
Der `AW_MUX_3` ist ein spezialisierter, generischer Multiplexer für die Adapter-basierte Kommunikation in IEC 61499-Systemen. Er ermöglicht die dynamische Auswahl einer von drei Quellen und eignet sich besonders für flexible Sensor-/Aktor-Routing in verteilten Automatisierungslösungen. Seine einfache Ereignissteuerung und die klare Schnittstelle machen ihn zu einem robusten Baustein für Standard-Multiplex-Anwendungen.