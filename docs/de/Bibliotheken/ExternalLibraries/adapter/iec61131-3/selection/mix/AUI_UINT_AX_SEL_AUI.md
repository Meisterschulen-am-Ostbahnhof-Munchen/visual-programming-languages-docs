# AUI_UINT_AX_SEL_AUI

![AUI_UINT_AX_SEL_AUI](./AUI_UINT_AX_SEL_AUI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein `AUI_UINT_AX_SEL_AUI` dient der binären Auswahl (Multiplexing) zwischen zwei Eingangsquellen und leitet das ausgewählte Signal an einen Ausgang weiter. Das Besondere an diesem Baustein ist die Kombination aus klassischen IEC 61499-Schnittstellen (diskreten Dateneingängen und Ereignissen) und modernen, adapterbasierten Verbindungsschnittstellen. 

Der Baustein ermöglicht es, flexibel zwischen einem adapterbasierten Signal (`IN0`) und einem direkt am Baustein anliegenden `UINT`-Wert (`IN1`) zu wechseln. Die Steuerung der Auswahl erfolgt über einen separaten Adapter-Eingang (`G`).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

* **EI1**: Löst die Übernahme und Verarbeitung des diskreten Dateneingangs `IN1` aus.

### **Ereignis-Ausgänge**

*(Keine direkten Ereignis-Ausgänge auf Bausteinebene vorhanden. Die Ereignisausgabe wird über den Ausgangs-Adapter `OUT` realisiert.)*

### **Daten-Eingänge**

* **IN1** (UINT): Auswählbare, diskrete Eingangsvariable (Datentyp `UINT`).

### **Daten-Ausgänge**

*(Keine direkten Daten-Ausgänge auf Bausteinebene vorhanden. Die Datenausgabe wird über den Ausgangs-Adapter `OUT` realisiert.)*

### **Adapter**

* **IN0** (Socket / Buchse, Typ: `adapter::types::unidirectional::AUI`): Auswählbarer Adapter-Eingang (Kanal 0). Erwartet ein unidirektionales `AUI`-Adaptersignal.
* **G** (Socket / Buchse, Typ: `adapter::types::unidirectional::AX`): Selektor-Eingang. Das empfangene Signal (Boolean auf `G.D1` mit Ereignis `G.E1`) bestimmt, welcher Eingang auf den Ausgang durchgeschaltet wird.
* **OUT** (Plug / Stecker, Typ: `adapter::types::unidirectional::AUI`): Der ausgewählte Ausgang als unidirektionales `AUI`-Adaptersignal.

---

## Funktionsweise

Der Baustein arbeitet intern mit einer Kombination aus Flip-Flops zur Zustandsspeicherung (`E_D_FF` und `E_D_FF_ANY`), Datenkopierern (`F_MOVE`) und dem Standard-Auswahlbaustein `F_SEL` nach IEC 61131-3.

1. **Signalpufferung**: 
   * Die Eingangsdaten aus dem Adapter `IN0` (`IN0.D1`) und dem diskreten Eingang `IN1` sowie das Selektorsignal `G.D1` werden bei Eintreffen ihrer jeweiligen Ereignisse (`IN0.E1`, `EI1`, `G.E1`) in internen Registern zwischengespeichert.
2. **Auswahllogik (`F_SEL`)**:
   * Wenn das Selektorsignal `G` den Zustand `FALSE` (0) hat, wird der Wert von `IN0` ausgewählt.
   * Wenn das Selektorsignal `G` den Zustand `TRUE` (1) hat, wird der Wert von `IN1` ausgewählt.
3. **Ausgabe**:
   * Nach der Auswahl wird der entsprechende Wert an den Ausgangs-Plug `OUT` übergeben. Gleichzeitig wird das Ausgangsereignis `OUT.E1` getriggert, um nachfolgende Programmteile über die Datenaktualisierung zu informieren.

---

## Technische Besonderheiten

* **Hybride Schnittstelle**: Der Baustein schließt die Lücke zwischen klassischer Verdrahtung (diskreter `UINT`-Eingang) und moderner Adapter-Verdrahtung.
* **Ereignisgesteuerte Zwischenspeicherung**: Durch die internen `E_D_FF`-Bausteine ist sichergestellt, dass auch asynchron eintreffende Daten und Ereignisse zuverlässig synchronisiert und fehlerfrei verarbeitet werden.
* **Unidirektionale Adapter**: Die Verwendung der Typen `AUI` und `AX` sorgt für einen ressourcenschonenden, unidirektionalen Datenfluss (nur in Senderichtung).

---

## Zustandsübersicht

| Selektor-Wert (`G.D1`) | Aktiver Kanal | Ausgangswert (`OUT.D1`) | Triggerung des Ausgangsereignisses (`OUT.E1`) |
| :--- | :--- | :--- | :--- |
| **FALSE** | Kanal 0 (`IN0`) | Wert von `IN0.D1` | Bei Änderung von `IN0.D1`, `IN0.E1` oder Flankenwechsel an `G` |
| **TRUE** | Kanal 1 (`IN1`) | Wert von `IN1` | Bei Änderung von `IN1`, `EI1` oder Flankenwechsel an `G` |

---

## Anwendungsszenarien

* **Sollwert-Umschaltung (Auto/Manuell)**: 
  Ein automatischer Sollwert wird kontinuierlich über ein Bussystem eingelesen und über den Adapter `IN0` bereitgestellt. Ein manueller Notwert oder Festwert kann direkt am Baustein über `IN1` vorgegeben werden. Ein Schlüsselschalter oder Software-Flag am Selektor `G` schaltet ereignisgesteuert zwischen beiden Werten um.
* **Modulare Maschinenarchitekturen**:
  Reduzierung des Verdrahtungsaufwands in komplexen 4diac-Anwendungen durch Kapselung von Signalgruppen in Adaptern, während gleichzeitig lokale Parameter flexibel anpassbar bleiben.

---

## Vergleich mit ähnlichen Bausteinen

* **Standard `F_SEL` (IEC 61131-3)**: Der Standard-Selektor arbeitet rein datenorientiert und unterstützt keine Adapter oder Ereignissynchronisation. `AUI_UINT_AX_SEL_AUI` erweitert diese Funktionalität um das ereignisbasierte Ausführungssystem der IEC 61499.
* **Standard-Kopierbausteine**: Im Gegensatz zu einfachen Routern oder Demultiplexern vereint dieser Baustein unterschiedliche Schnittstellentypen (Adapter und diskrete Variablen) in einer einzigen logischen Komponente.

---

## Fazit

Der `AUI_UINT_AX_SEL_AUI`-Baustein ist eine leistungsfähige und flexible Lösung für Umschalt- und Auswahllogiken in ereignisgesteuerten Systemen. Durch die nahtlose Integration von Adaptern und diskreten Datenleitungen trägt er erheblich zur Übersichtlichkeit und Modularität von 4diac-Applikationsnetzwerken bei.