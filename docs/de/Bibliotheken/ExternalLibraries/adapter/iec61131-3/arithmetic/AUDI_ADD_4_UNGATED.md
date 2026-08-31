# AUDI_ADD_4_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AUDI_ADD_4`](AUDI_ADD_4.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AUDI_ADD_4_UNGATED](./AUDI_ADD_4_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUDI_ADD_4_UNGATED` ist ein generischer Baustein zur Berechnung der arithmetischen Addition von vier Eingangswerten. Er ist als reiner Adapter-basierter Baustein ohne Ereignis‑ oder Datenschnittstellen realisiert. Die Verwendung von Adaptern ermöglicht eine flexible Kopplung mit anderen Bausteinen, die den gleichen Adaptertyp `adapter::types::unidirectional::AUDI` nutzen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine.

### **Ereignis-Ausgänge**

Keine.

### **Daten-Eingänge**

Der Baustein besitzt keine direkten Dateneingänge. Die zu addierenden Werte werden über Adaptereingänge bereitgestellt.

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Datenausgänge. Das Ergebnis wird über einen Adapterausgang weitergegeben.

### **Adapter**

| Bezeichnung | Richtung | Typ | Beschreibung |
| ------------- | ---------- | ----- | -------------- |
| `IN1` | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Erster Summand |
| `IN2` | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Zweiter Summand |
| `IN3` | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Dritter Summand |
| `IN4` | Socket (Eingang) | `adapter::types::unidirectional::AUDI` | Vierter Summand |
| `OUT` | Plug (Ausgang) | `adapter::types::unidirectional::AUDI` | Ergebnis der Addition |

## Funktionsweise

Der Baustein wartet auf gültige Werte an den Adaptereingängen `IN1` .. `IN4`. Sobald alle vier Eingänge einen Wert liefern, wird die Summe `IN1 + IN2 + IN3 + IN4` gebildet und über den `OUT`-Adapter ausgegeben. Die tatsächliche Datentypspezifikation erfolgt durch das generische Attribut `eclipse4diac::core::GenericClassName`, das auf `'GEN_AUDI_ADD'` gesetzt ist. Dadurch kann der Baustein für verschiedene numerische Datentypen (z. B. INT, REAL, LREAL) instanziiert werden, sofern der verwendete Adaptertyp `AUDI` diese unterstützt.

## Technische Besonderheiten

- **Reiner Adapterbaustein**: Der FB tauscht keine Ereignisse aus. Die Synchronisation erfolgt implizit durch die angeschlossenen Adapterverbindungen.
- **Generischer Datentyp**: Über die Attribute `GenericClassName` und `TypeHash` wird der konkrete Datentyp zur Laufzeit festgelegt. Dies ermöglicht eine wiederverwendbare Implementierung ohne Änderung der Logik.
- **Keine Zustandsautomaten**: Der FB enthält kein ECC (Execution Control Chart) – die Addition wird kontinuierlich oder auf Anforderung des Datenflusses durchgeführt.

## Zustandsübersicht

Der Baustein besitzt keine expliziten Zustände. Die Verarbeitung erfolgt datengetrieben: Sobald alle vier Eingangswerte verfügbar sind, wird das Ergebnis berechnet und ausgegeben.

## Anwendungsszenarien

- **Mittelwertbildung**: In Kombination mit einem nachgeschalteten Divisionsbaustein kann die Summe zur Berechnung eines Durchschnitts verwendet werden.
- **Summierung von Messwerten**: Zum Aufsummieren von vier analogen Eingangssignalen (z. B. Temperatur, Druck, Durchfluss) in einer Automatisierungslösung.
- **Kaskadierte Addition**: Mehrere `AUDI_ADD_4_UNGATED`-Bausteine lassen sich hintereinanderschalten, um eine größere Anzahl von Summanden zu verarbeiten.

## Vergleich mit ähnlichen Bausteinen

- **`ADD` (Standard-61499)**: Ein typischer ADD-Baustein besitzt Ereigniseingänge und Dateneingänge/-ausgänge. Der `AUDI_ADD_4_UNGATED` hingegen ist komplett adapterbasiert und besitzt keine Ereignisse, was eine stärkere Kopplung zwischen Bausteinen über Adapter erfordert.
- **`AUDI_ADD_2`**: Ein hypothetischer Baustein mit nur zwei Adaptereingängen – `AUDI_ADD_4_UNGATED` erweitert dies auf vier Summanden.
- **Generische FBs**: Durch das Attribut `GenericClassName` ähnelt der Baustein dem generischen Ansatz von IEC 61499, bei dem der Datentyp erst zur Laufzeit festgelegt wird.

- **[`AUDI_ADD_4`](AUDI_ADD_4.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der `AUDI_ADD_4_UNGATED` ist ein flexibler, reiner Adapterbaustein zur Addition von vier Werten. Dank seiner generischen Auslegung eignet er sich für verschiedene numerische Datentypen und kann in modularen Automatisierungsprojekten eingesetzt werden, die auf Adapter‑basierte Kommunikation setzen. Der Verzicht auf Ereignisse vereinfacht die Handhabung in datengetriebenen Systemen, erfordert jedoch eine korrekte Adapterverkabelung.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
