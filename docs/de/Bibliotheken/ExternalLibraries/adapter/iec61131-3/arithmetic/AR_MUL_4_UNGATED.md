# AR_MUL_4_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AR_MUL_4`](AR_MUL_4.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.


![AR_MUL_4_UNGATED](./AR_MUL_4_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AR_MUL_4_UNGATED` ist ein generischer arithmetischer Baustein, der zur Multiplikation von vier Eingangswerten dient. Er basiert auf einer Adapter-Schnittstelle, die eine saubere Kapselung und Strukturierung von Daten und dazugehörigen Ereignissen ermöglicht. Durch seine generische Natur (`GEN_AR_MUL`) kann sich der Baustein flexibel an verschiedene numerische Datentypen anpassen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der Baustein besitzt keine direkten, dedizierten Ereignis-Eingänge. Die Synchronisation und die Auslösung der Berechnung erfolgen implizit über die angeschlossenen Eingangs-Adapter.

### **Ereignis-Ausgänge**

Der Baustein besitzt keine direkten, dedizierten Ereignis-Ausgänge. Die Weiterleitung von Berechnungs- und Aktualisierungsereignissen erfolgt über den Ausgangs-Adapter.

### **Daten-Eingänge**

Es sind keine direkten Daten-Eingänge vorhanden. Die Werte für die Multiplikation werden über die Adapter-Schnittstellen eingelesen.

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge vorhanden. Das Ergebnis der Multiplikation wird über den Ausgangs-Adapter bereitgestellt.

### **Adapter**

Die Kommunikation mit anderen Bausteinen erfolgt ausschließlich über Adapter vom Typ `adapter::types::unidirectional::AR`:

- **Sockets (Eingangs-Adapter):**
  - `IN1`: Erster Multiplikand (Eingang 1).
  - `IN2`: Zweiter Multiplikand (Eingang 2).
  - `IN3`: Dritter Multiplikand (Eingang 3).
  - `IN4`: Vierter Multiplikand (Eingang 4).

- **Plugs (Ausgangs-Adapter):**
  - `OUT`: Das berechnete Produkt der vier Eingänge.

## Funktionsweise

Sobald über die Eingangs-Adapter (`IN1` bis `IN4`) neue Werte und die entsprechenden Trigger-Ereignisse eintreffen, multipliziert der Baustein die Werte miteinander. Das mathematische Verhalten entspricht der Formel:

$$\text{OUT} = \text{IN1} \times \text{IN2} \times \text{IN3} \times \text{IN4}$$

Das Ergebnis wird zusammen mit einem entsprechenden Aktualisierungsereignis über den Ausgangs-Adapter `OUT` ausgegeben.

## Technische Besonderheiten

- **Generisches Verhalten:** Durch das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `GEN_AR_MUL` ist der Baustein datentypunabhängig konzipiert. Er kann je nach Anwendung mit verschiedenen numerischen Datentypen (z. B. `INT`, `REAL`, `LREAL`) arbeiten, die vom Adaptertyp `AR` unterstützt werden.
- **Adapter-Kopplung:** Die Verwendung von unidirektionalen Adaptern (`AR`) reduziert den Verdrahtungsaufwand in der 4diac-IDE erheblich, da Daten und Steuerungsereignisse in einer einzigen Verbindung gebündelt werden.

## Zustandsübersicht

Da es sich um einen rein mathematischen Berechnungsbaustein handelt, ist der Baustein zustandslos. Jede Aktivierung führt direkt zur Berechnung des aktuellen Produkts basierend auf den anliegenden Werten der Eingangs-Adapter.

## Anwendungsszenarien

- **Signal-Skalierung:** Kalibrierung oder Anpassung von Sensorwerten, bei denen mehrere Faktoren (z. B. Grundwert, Verstärkung, Korrekturfaktor, Einheiten-Umrechnung) miteinander multipliziert werden müssen.
- **Physikalische Berechnungen:** Berechnung von komplexeren Größen wie Volumenströmen, elektrischer Leistung oder Energieflüssen, bei denen mehrere Messgrößen und konstante Faktoren einfließen.
- **Kaskaden-Vermeidung:** Zusammenfassung mehrerer Multiplikationsschritte in einem einzigen Baustein zur Erhöhung der Übersichtlichkeit im Applikationsdiagramm.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu herkömmlichen IEC 61131-3 `MUL`-Bausteinen, die oft nur zwei Eingänge besitzen und direkte Daten- und Ereignispins nutzen, bietet der `AR_MUL_4_UNGATED` durch die Zusammenfassung von vier Eingängen und die Verwendung von Adaptern eine wesentlich aufgeräumtere visuelle Darstellung im Steuerungsprogramm. Er verhindert die Notwendigkeit, mehrere Multiplizierer hintereinander zu schalten (Kaskadierung).

- **[`AR_MUL_4_UNGATED`](AR_MUL_4_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

- **[`AR_MUL_4`](AR_MUL_4.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `AR_MUL_4_UNGATED` ist ein praktischer Hilfsbaustein für arithmetische Operationen in der IEC 61499-Umgebung. Durch die konsequente Nutzung von Adaptern trägt er maßgeblich zur Übersichtlichkeit und Modularität von Steuerungsprogrammen bei, insbesondere bei der Verarbeitung komplexerer mathematischer Formeln.
