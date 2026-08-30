# ATM_AX_SEL_ATM


![ATM_AX_SEL_ATM](./ATM_AX_SEL_ATM.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `ATM_AX_SEL_ATM` dient als binärer Selektor (Multiplexer) für Adapter-Schnittstellen gemäß dem IEC 61499 Standard. Er ermöglicht es, basierend auf dem Zustand eines Auswahladapters (`G` vom Typ `AX`), dynamisch zwischen zwei Eingangsadaptern (`IN0` und `IN1` vom Typ `ATM`) zu wählen und das ausgewählte Signal an den Ausgangsadapter (`OUT` vom Typ `ATM`) weiterzuleiten. Der Baustein arbeitet rein ereignisgesteuert und ist intern für die Verarbeitung von zeitbasierten Signalen (`TIME`) ausgelegt.

## Schnittstellenstruktur

Der Funktionsbaustein besitzt keine direkt herausgeführten Standard-Ereignis- oder Datenpins. Die gesamte Kommunikation wird elegant über Sockets (Eingangs-Adapter) und Plugs (Ausgangs-Adapter) gekapselt.

### **Ereignis-Eingänge**

*Keine direkten Ereigniseingänge am FB-Körper vorhanden. Die Ereignissteuerung erfolgt implizit über die Adapter-Sockets.*

### **Ereignis-Ausgänge**

*Keine direkten Ereignisausgänge am FB-Körper vorhanden. Die Ereignissignalisierung erfolgt implizit über den Adapter-Plug.*

### **Daten-Eingänge**

*Keine direkten Dateneingänge am FB-Körper vorhanden.*

### **Daten-Ausgänge**

*Keine direkten Datenausgänge am FB-Körper vorhanden.*

### **Adapter**

#### **Sockets (Eingangs-Schnittstellen)**

- **IN0** (Typ: `adapter::types::unidirectional::ATM`):
  Der erste auswählbare Eingangsadapter (entspricht der Selektion bei logisch `FALSE`).
- **IN1** (Typ: `adapter::types::unidirectional::ATM`):
  Der zweite auswählbare Eingangsadapter (entspricht der Selektion bei logisch `TRUE`).
- **G** (Typ: `adapter::types::unidirectional::AX`):
  Der Auswahladapter (Selector). Das hier anliegende Signal bestimmt, welcher der beiden Eingänge an den Ausgang durchgeschaltet wird.

#### **Plugs (Ausgangs-Schnittstellen)**

- **OUT** (Typ: `adapter::types::unidirectional::ATM`):
  Der Ausgangsadapter, der die Daten und Ereignisse des jeweils selektierten Eingangs (`IN0` oder `IN1`) führt.

---

## Funktionsweise

Die interne Struktur des `ATM_AX_SEL_ATM` besteht aus einem Netzwerk standardisierter Hilfsbausteine, die eine zuverlässige und konsistente Signalweiterleitung sicherstellen:

1. **Ereigniserfassung und Pufferung**:
   Sobald an einem der Sockets (`IN0`, `IN1` oder `G`) ein Ereignis (`E1`) eintrifft, wird dieses über flankengetriggerte Flip-Flops (`E_D_FF_ANY` bzw. `E_D_FF`) erfasst. Die Datenwerte (`D1`) werden stabilisiert und an interne Puffer weitergegeben.
2. **Datenkonvertierung**:
   Die Daten der Eingänge `IN0` und `IN1` werden über zwei `F_MOVE`-Bausteine (konfiguriert auf den Datentyp `TIME`) gepuffert und für die Selektionslogik bereitgestellt.
3. **Auswahl (Selektion)**:
   Der Baustein `F_SEL` (ein Standard-Auswahlbaustein der IEC 61131-3) wertet den Zustand des Selektors `G` aus:
   - Ist das Signal von `G` gleich `FALSE`, wird der Wert von `IN0` gewählt.
   - Ist das Signal von `G` gleich `TRUE`, wird der Wert von `IN1` gewählt.
4. **Ausgabe**:
   Der ausgewählte Wert wird über einen weiteren `F_MOVE`-Baustein an den Ausgangsadapter `OUT` übergeben, woraufhin zeitgleich das Ausgangsereignis (`OUT.E1`) ausgelöst wird.

---

## Technische Besonderheiten

- **Adapter-Kapselung**: Durch die Verwendung von Adaptern anstelle von Einzelpins wird die Anzahl der Verbindungslinien im übergeordneten Steuerungsdiagramm drastisch reduziert, was die Lesbarkeit des Gesamtsystems verbessert.
- **Datentyp-Fokus**: Der Baustein ist intern durch die Parametrierung der `F_MOVE`-Bausteine speziell für den Datentyp `TIME` (Zeitwerte) optimiert.
- **Ereignisintegrität**: Die Verwendung von Ereignis-Flip-Flops stellt sicher, dass keine Signaländerung verloren geht und der Ausgang nur dann aktualisiert wird, wenn sich tatsächlich relevante Eingangsdaten oder der Selektor ändern.

---

## Zustandsübersicht

Da es sich um ein zusammengesetztes Funktionsbaustein-Netzwerk (Composite FB) handelt, besitzt der Baustein keine eigene klassische ECC (Event Execution Control) Zustandsmaschine. Das Verhalten ist rein datenfluss- und ereignisgesteuert:

| Zustand Selector `G.D1` | Triggerndes Ereignis | Zustand Ausgang `OUT.D1` | Ausgegebenes Ereignis |
| :--- | :--- | :--- | :--- |
| `FALSE` | Änderung an `IN0.E1` oder `G.E1` | Wert von `IN0.D1` | `OUT.E1` |
| `TRUE` | Änderung an `IN1.E1` oder `G.E1` | Wert von `IN1.D1` | `OUT.E1` |

---

## Anwendungsszenarien

- **Umschaltung von Prozesszeiten**: In industriellen oder landwirtschaftlichen Prozessen, bei denen zwischen zwei unterschiedlichen Takt-, Spül- oder Verzögerungszeiten (z. B. Sommer-/Winterbetrieb oder Rezeptur A/Rezeptur B) umgeschaltet werden muss.
- **Sollwert-Umschaltung**: Dynamische Auswahl eines zeitbasierten Sollwerts aus zwei unterschiedlichen Quellen basierend auf einer übergeordneten Betriebsart.

---

## Vergleich mit ähnlichen Bausteinen

- **Standard `F_SEL`**: Der klassische `F_SEL`-Baustein arbeitet direkt auf elementaren Datentypen und besitzt keine integrierte Ereignissteuerung für Adapter. `ATM_AX_SEL_ATM` verlagert diese Logik auf die strukturierte Adapter-Ebene.
- **Standard-Multiplexer**: Im Gegensatz zu universellen Multiplexern, die oft komplexe Bus-Strukturen aufweisen, ist dieser Baustein hochspezialisiert, extrem leichtgewichtig und perfekt auf die Kombination aus `ATM`- und `AX`-Adaptern abgestimmt.

---

## Fazit

Der `ATM_AX_SEL_ATM` ist ein robuster und wiederverwendbarer Hilfsbaustein für moderne Steuerungsarchitekturen nach IEC 61499. Er löst die Aufgabe der binären Signalumschaltung für zeitbasierte Datenströme auf elegante Weise unter Ausnutzung der Vorteile der Adapter-Technologie.
