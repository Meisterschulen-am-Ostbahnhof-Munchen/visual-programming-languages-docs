# ALI_TO_AUS


![ALI_TO_AUS](./ALI_TO_AUS.svg)

* * * * * * * * * *

## Einleitung

Der **ALI_TO_AUS** ist ein zusammengesetzter (Composite) Funktionsbaustein nach IEC 61499, der zur Umwandlung eines **ALI-Adapters** (Daten vom Typ **LINT**, Long Integer) in einen **AUS-Adapter** (Daten vom Typ **USINT**, Unsigned Short Integer) dient. Der Baustein kapselt die notwendige Konvertierungslogik, um eine einfache und typensichere Verbindung zwischen unterschiedlich typisierten Adapter-Schnittstellen zu ermöglichen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **ALI_IN.E1** (über Adapter-Socket) – löst die Konvertierung aus, sobald ein Ereignis von der angeschlossenen ALI-Quelle ankommt.

### **Ereignis-Ausgänge**

- **AUS_OUT.E1** (über Adapter-Plug) – signalisiert den Abschluss der Konvertierung an die nachgeschaltete AUS-Senke.

### **Daten-Eingänge**

- **ALI_IN.D1** (über Adapter-Socket) – der zu konvertierende LINT-Wert (Long Integer).

### **Daten-Ausgänge**

- **AUS_OUT.D1** (über Adapter-Plug) – der konvertierte USINT-Wert (Unsigned Short Integer).

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket (Eingang)** | ALI_IN | adapter::types::unidirectional::ALI | Empfängt den LINT-Datenwert und das zugehörige Ereignis |
| **Plug (Ausgang)**  | AUS_OUT | adapter::types::unidirectional::AUS   | Stellt den konvertierten USINT-Wert und das Bestätigungsereignis bereit |

## Funktionsweise

Der Baustein enthält intern eine Instanz des Funktionsbausteins **F_LINT_TO_USINT** aus der IEC 61131-Konvertierungsbibliothek. Der Ablauf ist:

1. Ein Ereignis **ALI_IN.E1** triggert die Datenübernahme.
2. Der an **ALI_IN.D1** anliegende LINT-Wert wird an den Eingang **IN** des internen Konverters weitergeleitet.
3. Der interne Baustein führt die Typumwandlung von LINT nach USINT durch (Beachtung von Wertebereichsgrenzen).
4. Nach erfolgreicher Konvertierung erzeugt der interne Baustein ein **CNF**-Ereignis, das als **AUS_OUT.E1** ausgegeben wird.
5. Das konvertierte Ergebnis gelangt von **OUT** des internen Bausteins an **AUS_OUT.D1**.

Die Kopplung von Ereignis- und Datenflüssen erfolgt vollständig über das interne Netzwerk; der Anwender sieht nur die beiden Adapter-Schnittstellen.

## Technische Besonderheiten

- **Wiederverwendbarer Konverter**: Der Baustein setzt auf den standardisierten **F_LINT_TO_USINT** (iec61131::conversion), sodass die Konvertierungslogik nicht neu implementiert werden muss.
- **Adapter‑basiert**: Die gesamte Schnittstelle ist als Uni‑Directional‑Adapter realisiert, vereinfacht den Austausch und die Wiederverwendung in größeren Systemen.
- **Lizenz**: Der Baustein wird unter der **Eclipse Public License 2.0** bereitgestellt (EPL-2.0).

## Zustandsübersicht

Da es sich um einen Composite‑Baustein handelt, existiert keine explizite Zustandsmaschine auf oberster Ebene. Der interne Konverter **F_LINT_TO_USINT** arbeitet ereignisgesteuert und führt nach jedem **REQ**‑Ereignis genau einen Konvertierungsschritt durch. Solange kein Ereignis anliegt, bleibt der Baustein inaktiv.

## Anwendungsszenarien

- **Schnittstellenanpassung**: Verbindung von Komponenten, die mit **LINT** (z. B. hochauflösende Zähler) arbeiten, mit solchen, die **USINT** (z. B. einfache Aktorsteuerungen) erwarten.
- **Systemintegration**: Wenn ein vorgegebener Adapter‑Typ (ALI) vorhanden ist und ein anderer Adapter‑Typ (AUS) benötigt wird – z. B. beim Zusammenschluss von Modulen verschiedener Hersteller.
- **Protokoll‑Wandlung**: Einsatz in Datenvorverarbeitungsketten, bei denen lange Integerwerte auf einen kleineren Bereich abgebildet werden müssen.

## Vergleich mit ähnlichen Bausteinen

Es existieren zahlreiche datentyp‑spezifische Konvertierungsbausteine (z. B. LINT_TO_INT, LINT_TO_DINT, USINT_TO_LINT). Der **ALI_TO_AUS** hebt sich hervor, indem er nicht nur die reine Typumwandlung kapselt, sondern diese direkt in eine **Adapter‑Schnittstelle** einbettet. Dies reduziert den Verdrahtungsaufwand auf der Blockebene und erhöht die Lesbarkeit des Gesamtentwurfs.

## Fazit

Der **ALI_TO_AUS** ist ein praktischer und robuster Baustein zur Umwandlung von LINT‑Adapter‑Daten in USINT‑Adapter‑Daten. Durch die Nutzung eines standardisierten Konverters und die klare Adapter‑Kapselung wird eine wiederverwendbare, typensichere und wartungsfreundliche Lösung für unterschiedliche Steuerungssysteme bereitgestellt.