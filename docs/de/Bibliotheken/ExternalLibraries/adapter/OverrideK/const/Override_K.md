# Override_K

![Override_K](./Override_K.svg)

* * * * * * * * * *

## Einleitung

Das globale Konstantenpaket `Override_K` stellt die drei benannten `UINT`-Werte bereit, mit denen
[Override_K_Select](../Override_K_Select.md) seinen `K`-Ausgang für `AX_AUI_MUX_3` befüllt.
Statt `UINT#0`/`UINT#1`/`UINT#2` als Literale in den `F_SEL`-Parametern zu verdrahten, referenziert
der Baustein diese drei Konstanten über ihren sprechenden Namen. Das Paket ist im Namensraum
`adapter::OverrideK::const` definiert.

## Schnittstellenstruktur

Da es sich um ein Paket mit globalen Konstanten handelt, besitzt es keine ereignis- oder
datenflussbasierten Schnittstellen im herkömmlichen Sinne eines Funktionsbausteins.

### **Ereignis-Eingänge**

Nicht vorhanden.

### **Ereignis-Ausgänge**

Nicht vorhanden.

### **Daten-Eingänge**

Nicht vorhanden.

### **Daten-Ausgänge**

Nicht vorhanden.

### **Adapter**

Nicht vorhanden.

## Funktionsweise

Die Konstanten werden beim Kompilieren durch ihre fest definierten Werte ersetzt:

*   `Override_K_Normal`: `UINT#0` — K-Wert für "kein Override" (`AX_AUI_MUX_3.IN1`, Normalwert).
*   `Override_K_ForceFalse`: `UINT#1` — K-Wert für "Override auf FALSE erzwungen"
    (`AX_AUI_MUX_3.IN2`).
*   `Override_K_ForceTrue`: `UINT#2` — K-Wert für "Override auf TRUE erzwungen"
    (`AX_AUI_MUX_3.IN3`).

## Technische Besonderheiten

*   **Direkte Kopplung an `AX_AUI_MUX_3`-Eingangsreihenfolge.** Die Zahlenwerte 0/1/2 entsprechen
    exakt der Eingangsnummerierung von `AX_AUI_MUX_3` (`IN1`/`IN2`/`IN3`) — eine Änderung dieser
    Reihenfolge in [Override_K_Select](../Override_K_Select.md) müsste hier mit gepflegt werden.
*   **Nur von `Override_K_Select` verwendet.** Anders als z. B. `OPC_UA_Endpoints` ist dieses
    Paket eng an einen einzigen Baustein gekoppelt, nicht an mehrere unabhängige Verwendungsstellen.

## Zustandsübersicht

Da es sich um statische, konstante Werte handelt, existiert kein Zustandsautomat.

## Anwendungsszenarien

*   Referenzierung in den `IN0`/`IN1`-`Parameter`-Werten der beiden `F_SEL`-Bausteine in
    [Override_K_Select](../Override_K_Select.md).
*   Vergleichswerte, falls ein Konsument den rohen `K`-Wert eines `AX_AUI_MUX_3` auswerten möchte,
    statt nur den gemuxten Ausgangswert zu verwenden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

*   **[IDs](../../../isobus/UT/Q/const/IDs.md)** (ISOBUS-UT-Bibliothek): folgt demselben GCF-
    Muster (benannte Konstanten statt Literale), deckt aber ISOBUS-Objekt-IDs ab statt eines
    MUX-Selektors.

## Fazit

`Override_K` ist ein kleines, eng gekoppeltes Konstantenpaket, das die drei K-Werte von
`Override_K_Select` benennt und damit lesbarer und wartbarer macht als verstreute `UINT#0/1/2`-
Literale.
