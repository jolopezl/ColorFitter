C... Jorge Lopez
C... February 2015
C-----------------------------------------------------------------
C...Preamble: declarations.
C...All real arithmetic in double precision.
      IMPLICIT DOUBLE PRECISION(A-H, O-Z)
C...Three Pythia functions return integers, so need declaring.
      INTEGER PYK,PYCHGE,PYCOMP
C...EXTERNAL statement links PYDATA on most machines.
      EXTERNAL PYDATA
C-----------------------------------------------------------------
C...Commonblocks.
C...The event record.
      COMMON/PYJETS/N,NPAD,K(4000,5),P(4000,5),V(4000,5)
C...Parameters.
      COMMON/PYDAT1/MSTU(200),PARU(200),MSTJ(200),PARJ(200)
C...Particle properties + some flavour parameters.
C      COMMON/PYDAT2/KCHG(500,4),PMAS(500,4),PARF(2000),VCKM(4,4)
C...Decay information.
C      COMMON/PYDAT3/MDCY(500,3),MDME(8000,2),BRAT(8000),KFDP(8000,5)
C...Selection of hard scattering subprocesses.
      COMMON/PYSUBS/MSEL,MSELPD,MSUB(500),KFIN(2,-40:40),CKIN(200)
C...Parameters. 
      COMMON/PYPARS/MSTP(200),PARP(200),MSTI(200),PARI(200)
      COMMON/PYDATR/MRPY(6),RRPY(100)
C-----------------------------------------------------------------
C... Requiered variables
      INTEGER I
      DOUBLE PRECISION Z, PZ, NU, XB, ZL
      DOUBLE PRECISION q0, q1, q2, q3, W2
      DOUBLE PRECISION EB, ES
      DOUBLE PRECISION ELECTRON_MASS, PROTON_MASS
C...Files requiered to save output
      OPEN(10,file='pythia_run_output.txt',status='unknown')
      OPEN(20,file='pythia_run_output_Q2nu.txt',status='unknown')
C...Set some useful values
      ELECTRON_MASS = 5.1000000000000004E-004
      PROTON_MASS   = 0.93827000000000005
C...First section: initialization.
C...Main parameters of run: number of events and PYINIT inputs
C...Energy should be given in the laboratory frame
C...For Hermes the energy of the electron beam is 27.6 GeV
C...The energy is given in the selected frame Pythia will transformations as it requieres them
      NEV=10000!0000000
      WIN=27.6D0 ! HERMES
C     WIN=6 ! JLab .
C     WIN=12 ! JLab upgrad.
C...Minimum cms energy to make this work
      PARP(2)=0.1
C...Choose fragmentation scheme
      MSTJ(1)=1 ! selects Lund model - anyhow, its the default, just for knowing it
      PARJ(41)=0.30 ! a fragmentation parameter
      PARJ(42)=0.58 ! b fragmentation parameter
C...Get events with Q2>1
      CKIN(65)=1D0
      CKIN(67)=1D0
C-----------------------------------------------------------------
      MRPY(1) = 0
C       MSUB(131) = 0
C       MSUB(132) = 0
C       MSUB(135) = 0
C       MSUB(135) = 0
C...Initialize PYINIT
      CALL PYINIT('FIXT','gamma/e-','p',WIN)
C...Begin event loop.
      DO 100 IEV=1,NEV
  200    CALL PYEVNT
C        CALL PYLIST(1)
C...This parameters check if we have errors
C...I should create a while loop make NEV events without errors
        IF(MSTI(61).EQ.1) THEN
          WRITE(*,*)'Error whith MSTI(61)'
		      EXIT
        ENDIF
        EB = P(1,4)
        ES = P(3,4)
C... compute Q2 = -q2 where q=p1-p3
        q0 = P(1,4)-P(3,4)
        q1 = P(1,1)-P(3,1)
        q2 = P(1,2)-P(3,2)
        q3 = P(1,3)-P(3,3)
        Q2 = q0*q0-q1*q1-q2*q2-q3*q3
        Q2 = -Q2
        IF((Q2.GT.(2.4+0.5)).OR.(Q2.LT.(2.4-0.5))) THEN 
          GOTO 200
        ENDIF
        NU = EB-ES
        IF((NU.GT.(12.4+1)).OR.(NU.LT.(12.4-1))) THEN
          GOTO 200
        ENDIF
        XB = Q2/(2*PROTON_MASS*NU)
        W2 = PROTON_MASS*PROTON_MASS-Q2+2*PROTON_MASS*NU
C... Loop over TRACKS and print some variables only for DIS
        IF(MSTI(1)==99) THEN
C        IF( (Q2.GT.1).and.(W2.GT.4) ) THEN
          WRITE(20,*)Q2,NU,XB,W2
          DO 201 I=1,N
            Z=P(I,4)/NU
            PZ=P(I,3)
            IF(K(I,2)==211) THEN
              WRITE(10,*)Z,XB,Q2,NU,W2 !,P(I,4),PZ,P(I,4)+PZ,PROTON_MASS+2*NU
            ENDIF
  201     CONTINUE
        ENDIF
C...List first few events.
C        IF(IEV.LE.2) THEN
C          CALL PYLIST(1)
C        ENDIF
        IF(MOD(IEV,50000)==0) WRITE(*,*) "EVENT ",IEV," OF ",NEV
C...End event loop.
  100 CONTINUE
      WRITE(*,*) "END of Monte Carlo Event Generation"
C-----------------------------------------------------------------
      CLOSE(10)
      CLOSE(20)
      END
C... End
C.3456789012345678901234567890123456789012345678901234567890123456789012
