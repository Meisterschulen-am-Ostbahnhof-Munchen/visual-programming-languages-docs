# SET_DATE_AND_TIME


![SET_DATE_AND_TIME](./SET_DATE_AND_TIME.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock SET_DATE_AND_TIME dient dazu, einen eingehenden DATE_AND_TIME-Wert auf eine Zielvariable zu schreiben. Die Zielvariable wird als InOut-Parameter übergeben, sodass sie sowohl gelesen als auch beschrieben werden kann. Der Baustein realisiert eine einfache Zuweisungsoperation, die durch ein Ereignis ausgelöst wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Normaler Ausführungsanforderung; startet das Schreiben des Eingangswerts in die InOut-Variable. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigung der abgeschlossenen Ausführung. |

### **Daten-Eingänge**

| Name | Typ           | Beschreibung |
|------|---------------|--------------|
| IN   | DATE_AND_TIME | Der Wert, der in die Zielvariable geschrieben werden soll. |

### **Daten-Ausgänge**

Der Baustein besitzt keine expliziten Daten-Ausgänge. Der aktualisierte Wert wird über den InOut-Parameter `OUT` nach außen sichtbar.

### **Adapter**

Keine.

## Funktionsweise

Sobald ein Ereignis am Eingang `REQ` anliegt, wird die ST-Anweisung `OUT := IN` ausgeführt. Der Wert des Eingangs `IN` wird direkt in die InOut-Variable `OUT` kopiert. Nach erfolgreichem Abschluss wird der Ausgang `CNF` getriggert, um die Fertigstellung zu signalisieren. Die Verwendung einer InOut-Variable erlaubt es, den Baustein in eine bestehende Datenverbindung einzufügen, ohne eine separate Ausgangsvariable zu benötigen.

## Technische Besonderheiten

- **InOut-Variable:** Der Parameter `OUT` ist als InOut deklariert. Dadurch kann der Baustein den Wert der verbundenen Variable direkt überschreiben und gleichzeitig nach außen hin lesbar sein.
- **Einfache Zuweisung:** Es handelt sich um eine reine Kopieroperation ohne Typkonvertierung oder Plausibilitätsprüfung.
- **Keine Zustandsautomaten:** Der Baustein ist als SimpleFB mit nur einem EZ-Zustand (REQ) realisiert. Die Ausführung erfolgt streng in einem Zyklus.

## Zustandsübersicht

Der Baustein besitzt einen einzigen Zustand:

| Zustand | Aktion                           | Ausgabeereignis |
|---------|----------------------------------|-----------------|
| REQ     | `OUT := IN`                      | CNF             |

Der Zustandsautomat startet bei Erhalt von `REQ` in diesem Zustand, führt die Aktion aus und sendet sofort `CNF`.

## Anwendungsszenarien

- **Initialisierung einer Systemzeit:** Ein übergeordneter Baustein kann eine aktuelle Zeit (z. B. von einer Schnittstelle) über `IN` bereitstellen und über `SET_DATE_AND_TIME` in eine globale oder persistent gespeicherte Zeitvariable (InOut) schreiben.
- **Rücksetzen einer Zeitvariablen:** Beim Setzen eines Referenzzeitpunkts kann der Baustein genutzt werden, um einen vorgegebenen Wert in eine übergeordnete Variable zu übernehmen.
- **Parametrierung:** In Regel-/Steuerungsanwendungen kann der Baustein dazu verwendet werden, Soll-Zeitwerte in Datenbausteine zu schreiben.

## Vergleich mit ähnlichen Bausteinen

Einfache Zuweisungsbausteine für andere Datentypen (z. B. `SET_VALUE` für integer oder bool) folgen dem gleichen Muster. Der `SET_DATE_AND_TIME` ist speziell auf den Typ `DATE_AND_TIME` zugeschnitten und bietet keine erweiterten Funktionen wie Addition oder Subtraktion. Im Unterschied zu einem `MOVE`-Baustein (der Eingang auf Ausgang legt) verwendet dieser Baustein eine InOut-Variable, sodass die Quelle und das Ziel nicht getrennt werden müssen.

## Fazit

Der Funktionsblock `SET_DATE_AND_TIME` ist ein einfacher, aber nützlicher Baustein zum Überschreiben einer Datums- und Zeitvariablen innerhalb eines IEC 61499-Systems. Durch die Verwendung einer InOut-Schnittstelle lässt er sich leicht in bestehende Datenflüsse integrieren. Aufgrund seiner schlichten Struktur ist er effizient und für alle Szenarien geeignet, in denen eine gezielte Zuweisung eines Datum-Zeit-Werts erforderlich ist.