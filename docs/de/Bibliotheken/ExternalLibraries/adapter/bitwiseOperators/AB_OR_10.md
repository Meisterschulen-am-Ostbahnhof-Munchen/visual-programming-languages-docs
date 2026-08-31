# AB_OR_10

![AB_OR_10](./AB_OR_10.svg)

* * * * * * * * * *

## Einleitung

Der **AB_OR_10** ist ein generischer Funktionsblock zur bitweisen ODER-Verknüpfung von 10 Eingangswerten vom Typ `BYTE` (8-Bit-Bitmuster (Byte)). Im Gegensatz zur booleschen Verknüpfung einzelner Wahrheitswerte (wie bei den `AX_OR`-Bausteinen) wird hier jedes einzelne Bit des Datenworts unabhängig verknüpft.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**

Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge vorhanden

### **Adapter**

**Eingangsadapter:**

- **IN1**: ODER-Eingang 1 (Typ: adapter::types::unidirectional::AB)
- **IN2**: ODER-Eingang 2 (Typ: adapter::types::unidirectional::AB)
- **IN3**: ODER-Eingang 3 (Typ: adapter::types::unidirectional::AB)
- **IN4**: ODER-Eingang 4 (Typ: adapter::types::unidirectional::AB)
- **IN5**: ODER-Eingang 5 (Typ: adapter::types::unidirectional::AB)
- **IN6**: ODER-Eingang 6 (Typ: adapter::types::unidirectional::AB)
- **IN7**: ODER-Eingang 7 (Typ: adapter::types::unidirectional::AB)
- **IN8**: ODER-Eingang 8 (Typ: adapter::types::unidirectional::AB)
- **IN9**: ODER-Eingang 9 (Typ: adapter::types::unidirectional::AB)
- **IN10**: ODER-Eingang 10 (Typ: adapter::types::unidirectional::AB)

**Ausgangsadapter:**

- **OUT**: ODER-Ergebnis (Typ: adapter::types::unidirectional::AB)

## Funktionsweise

Sobald an einem der 10 Eingangsadapter (`IN1` … `IN10`) ein Ereignis eintrifft, verknüpft der Baustein die Bitmuster aller 10 Eingänge bitweise mit **ODER** und schreibt das Ergebnis auf den Ausgangsadapter `OUT`. Als Startwert der Verknüpfung dient das neutrale Element (alle Bits gelöscht / 0 (Nullelement der ODER-Verknüpfung)), sodass bei nur einem tatsächlich angeschlossenen Eingang dessen Wert unverändert durchgereicht wird.

Nur wenn sich das neu berechnete Ergebnis vom aktuell auf `OUT` gehaltenen Wert unterscheidet, wird `OUT` neu beschrieben und dessen Adapter-Event gesendet (siehe „Änderungserkennung" unten).

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AB_OR`) definiert und deckt über den GenericClassName-Mechanismus alle Aritäten (2 bis 10 Eingänge) derselben Grundlogik ab.
- **Bitweise Verknüpfung**: Anders als bei den booleschen `AX_OR`-Bausteinen wird hier jedes Bit des `BYTE`-Datenworts einzeln verknüpft, nicht nur ein einzelner Wahrheitswert.
- **Unidirektionale Adapter**: Alle Adapter sind vom Typ `unidirectional::AB` – die Daten fließen nur vom Socket zum Plug.
- **Normkonformität**: Der Baustein implementiert die Verknüpfung gemäß IEC 61499-2 / IEC 61131-3.

## Zustandsübersicht

Da es sich um einen kombinatorischen Logikbaustein handelt, besitzt der AB_OR_10 keine internen Zustände. Die Ausgabe wird bei jedem eingehenden Ereignis direkt aus den aktuellen Eingangswerten neu berechnet.

## Anwendungsszenarien

- **Bitmasken-Verknüpfung**: Kombinieren mehrerer Statusregister oder Flag-Bytes vom Typ `BYTE` zu einem Gesamtergebnis.
- **Signalaggregation**: Zusammenführen mehrerer `BYTE`-Datenquellen (z. B. aus verschiedenen Modulen) über eine gemeinsame ODER-Verknüpfung.
- **Diagnose- und Statusauswertung**: Prüfen von Bitmustern auf gemeinsame oder unterschiedliche gesetzte Bits.

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu `AX_OR_10`, der einzelne boolesche Wahrheitswerte verknüpft, arbeitet `AB_OR_10` auf dem vollständigen Bitmuster eines `BYTE`-Werts. Verglichen mit dem Standard-Baustein [OR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/OR_2.md) verwendet `AB_OR_10` Adapter-basierte Schnittstellen anstelle direkter Daten-/Ereignisein-/ausgänge, was eine flexiblere Integration in Adapter-basierte Systemarchitekturen ermöglicht.

- **[`AB_OR_10_UNGATED`](AB_OR_10_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Das Ergebnis wird nur auf den Ausgangs-Plug (`OUT`) geschrieben und dessen Adapter-Event nur gesendet, wenn sich der neu berechnete Wert vom aktuell auf `OUT` gehaltenen Wert unterscheidet. Bleibt das Ergebnis unverändert, wird kein Adapter-Event gesendet -- so werden überflüssige Updates bei nachgeschalteten Peers vermieden.

## Fazit

Der **AB_OR_10** bietet eine zuverlässige, generische Implementierung der bitweisen ODER-Funktion für `BYTE`-Werte mit Adapter-basierten Schnittstellen. Seine generische Natur macht ihn vielseitig einsetzbar in Automatisierungsprojekten, die nach IEC 61499-Standard entwickelt werden und mehrere Bitmuster desselben Datentyps kombinieren müssen.
