# Uebung_010d_PC_A_OPC

![Uebung_010d_PC_A_OPC_network](./Uebung_010d_PC_A_OPC_network.svg)

* * * * * * * * * *

## Einleitung

`Uebung_010d_PC_A_OPC` ist die Geraet-A-Seite (Station 11, 192.168.1.11) der PC-zu-PC-OPC-UA-Variante von Uebung 010d (Toggle-Flipflop via SoftKey): ein SoftKey-Tastendruck ruft per `CLIENT_0` einen argument- und rueckgabewertlosen OPC-UA-Methodenaufruf auf Geraet B auf (reiner RPC-Trigger, kein Wertwechsel-Trick noetig, keine Toggle-Logik auf diesem Geraet). `GreenWhiteBackground1_AX` zeigt den von Geraet B lokal ueberwachten Flipflop-Zustand. "SUB style": das Protokoll steckt im `MyLib::sys`-Composite, nicht in der Resource des Geraets - Gegenstueck: [`Uebung_010d_PC_B_OPC`](./Uebung_010d_PC_B_OPC.md).

## Verwendete Funktionsbausteine (FBs)

- **SoftKey_UP_F1** (`isobus::UT::io::Softkey::Softkey_IE`): physischer SoftKey (F1), `InputEvent=SK_RELEASED`.
- **TRIGGER_CLIENT** (`iec61499::net::CLIENT_0`): ruft die argumentlose Remote-Methode unter `ID_TRIGGER_CALL` auf.
- **STATE_SUBSCRIBE** (`adapter::net::AX_SUBSCRIBE_1`): abonniert den von Geraet B geschriebenen Flipflop-Zustand unter `ID_STATE_READ`.
- **GreenWhiteBackground_AX** (SubApp, Typ `MyLib::sys::GreenWhiteBackground1_AX`): zeigt den abonnierten Zustand am SoftKey an.

## Zusammenfassung

Geraet-A-Seite eines PC-zu-PC-Toggle-Triggers: SoftKey ruft eine Remote-Methode auf, der tatsaechliche Flipflop-Zustand kommt zurueckgemeldet von Geraet B.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
