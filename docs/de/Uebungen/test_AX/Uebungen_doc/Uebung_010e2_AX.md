# Uebung_010e2_AX: SR+Toggle-Flipflop mit 3x SoftKey und GreenWhiteBackground mit Typed Subapp

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_010e2_AX`.

----

## Ziel der Übung

Wiederverwendbarkeit durch Typisierung.

-----

## Beschreibung

Hier wurde aus der untypisierten SR+Toggle-Flipflop-Schaltung aus `Uebung_010e_AX` ein echter Typ `Uebung_010e2_sub_AX` erstellt.
Er hat die Parameter `u16ObjId_SET`, `u16ObjId_RESET`, `u16ObjId_TOGGLE` (welcher SoftKey löst welche Aktion aus?) und `Output` (welcher Ausgang?).

-----

## Vorteil

Man kann diesen "Smart SR+Toggle-Softkey"-Baustein nun beliebig oft in der Bibliothek verwenden.
