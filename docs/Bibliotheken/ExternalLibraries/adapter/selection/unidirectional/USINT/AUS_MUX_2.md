# AUS_MUX_2


![AUS_MUX_2](./AUS_MUX_2.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AUS_MUX_2** realisiert einen generischen Multiplexer für den AUS-Adapter-Typ (unidirektional). Er wählt zwischen zwei Eingangsadaptern (`IN1` und `IN2`) aus und leitet deren Signal an den Ausgangsadapter (`OUT`) weiter. Die Auswahl erfolgt über den Index `K`. Der Baustein wird über das Ereignis `REQ` angesteuert und quittiert mit `CNF`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Mit Variablen | Kommentar                       |
|----------|---------------|---------------------------------|
| REQ      | K             | Setzt den Index K und löst die Multiplexer-Aktion aus |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar                              |
|----------|----------------------------------------|
| CNF      | Bestätigung der erfolgten Umschaltung |

### **Daten-Eingänge**

| Variable | Typ  | Kommentar               |
|----------|------|-------------------------|
| K        | UINT | Index zur Auswahl des Eingangs (0 → IN1, 1 → IN2) |

### **Daten-Ausgänge**

Keine separaten Datenausgänge definiert; die Übergabe erfolgt über den Adapter `OUT`.

### **Adapter**

| Typ     | Name | Richtung   | Adapter-Typ                           | Kommentar                              |
|---------|------|------------|---------------------------------------|----------------------------------------|
| Plug    | OUT  | Output     | adapter::types::unidirectional::AUS   | Ausgang, der den gewählten Eingang liefert |
| Socket  | IN1  | Input      | adapter::types::unidirectional::AUS   | Erster Eingang (K = 0)                 |
| Socket  | IN2  | Input      | adapter::types::unidirectional::AUS   | Zweiter Eingang (K = 1)                |

## Funktionsweise

Bei einem **REQ**-Ereignis wird der Wert des Indexes `K` ausgewertet:

- Ist `K = 0`, wird das Signal von `IN1` auf den Adapter `OUT` geschaltet.
- Ist `K = 1`, wird das Signal von `IN2` auf `OUT` geschaltet.
- Für andere Werte von `K` (z. B. >1) ist das Verhalten nicht spezifiziert; der Baustein sollte daher nur mit `K = 0` oder `1` betrieben werden.

Nach erfolgter Umschaltung wird ein **CNF**-Ereignis ausgegeben.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist als generischer Funktionsblock deklariert (Attribut `GenericClassName = 'GEN_AUS_MUX'`). Er kann durch die 4diac-IDE automatisch instanziiert werden.
- **Adapter-basiert**: Die Ein- und Ausgänge sind als unidirektionale AUS-Adapter realisiert, sodass komplexe Datenstrukturen oder Bus-Signale gebündelt übertragen werden können.
- **Paketstruktur**: Der Baustein ist im Namensraum `adapter::selection::unidirectional` abgelegt, was auf seine systematische Einordnung in eine Bibliothek für Selektionsfunktionen hinweist.
- **Ereignisgesteuert**: Die Umschaltung erfolgt nur bei expliziter Anforderung (REQ), nicht zyklisch.

## Zustandsübersicht

Eine explizite Zustandsmaschine ist in der XML nicht hinterlegt. Der Baustein arbeitet funktional:

1. **Warten** – auf ein `REQ`-Ereignis
1. **Verarbeitung** – Auswertung von `K` und Weiterleitung des entsprechenden Eingangs an `OUT`
1. **Quittieren** – Senden von `CNF`
1. Rückkehr in den Wartezustand

## Anwendungsszenarien

- **Umschaltung zwischen zwei Sensoren**: In einer landwirtschaftlichen Maschine kann zwischen zwei AUS-kompatiblen Sensorwerten (z. B. GPS vs. Odometrie) umgeschaltet werden.
- **Betriebsmodus-Auswahl**: In einer Steuerung wird zwischen zwei unterschiedlichen Konfigurationsdatenströmen gewählt – etwa Normalbetrieb und Wartungsmodus.
- **Redundanz-Umschaltung**: Ausweichen auf einen zweiten AUS-Datenkanal, falls der primäre ausfällt.

## Vergleich mit ähnlichen Bausteinen

- **Ereignis-MUX (z. B. MUX_2)** – Wählt zwischen zwei Ereignispfaden; hier liegt der Fokus auf dem Adaptersignal.
- **Daten-Multiplexer (z. B. SEL, MUX_INT)** – Arbeiten mit einfachen Datentypen (INT, BOOL) und haben separate Ausgangsvariablen. `AUS_MUX_2` nutzt dagegen komplette Adapter-Schnittstellen, was eine gekapselte Übergabe komplexer Informationen ermöglicht.

## Fazit

Der `AUS_MUX_2` ist ein kompakter, adapterbasierter Funktionsblock zur Auswahl eines von zwei AUS-Signalen. Durch den generischen Aufbau und die klare Ereignissteuerung eignet er sich besonders für modulare Automatisierungslösungen im Umfeld der IEC 61499, wo standardisierte Adapter für den Datenaustausch verwendet werden.